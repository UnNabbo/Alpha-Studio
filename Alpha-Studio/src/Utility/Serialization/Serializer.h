#pragma once

#include <string>
#include "Core/Core.h"
#include <typeinfo>  
#include <memory>
#include <concepts>
#include <fstream>
#include <unordered_map>
#include <any>

#include "BinaryData.h"

//!!! DISCLAMER: CODE IS HOT GARBAGE THAT NEEDS TO BE REWRITTEN ASAP !!!

//TODO REDUCE TEMPLATES

namespace Alpha {
	namespace Utils {
		static std::vector<std::string> SeparateTypesLiterals(std::string& literals) {
			literals.erase(remove(literals.begin(), literals.end(), ' '), literals.end());
			std::vector<std::string> type_string_literal;

			uint32_t offset = 0;
			while (true) {
				size_t index = literals.find(',', offset);
				if (index != std::string::npos) {
					type_string_literal.push_back(literals.substr(offset, index));
					offset = index + 1;
				}
				else {
					type_string_literal.push_back(literals.substr(offset, literals.length()));
					break;
				}
			}
			return type_string_literal;
		}

		static size_t CalculateBinarySize(Serializer::BinaryData& data) {
			size_t offset = 0;
			offset += data.Data_Size;
			offset += data.Identifer_Size;
			offset += sizeof(size_t) * 3;
			return offset;
		}
		
	}

	namespace Serializer {
		template<typename T>
		struct NameValuePair {
			std::string Name;
			T& Value;
		};

		template<typename>
		struct is_namevaluepair : std::false_type {};

		template<typename T>
		struct is_namevaluepair<NameValuePair<T>> : std::true_type {};


		struct BinaryArchive { };

		template<typename T, typename S = T>
		struct VecReference {
			VecReference(std::vector<S>& Vector, uint64_t index) : m_Vector(&Vector), m_Index(index) { }
			VecReference(std::vector<S>& Vector) : m_Vector(&Vector), m_Index(-1), m_Is_Empty(true) { }
			VecReference() : m_Index(-1), m_Is_Empty(true) { }
			operator T() const { 
				if (m_Is_Empty) {
					return *(T*)nullptr;
				}
				return *(T*)&(*m_Vector)[m_Index];
			}

			VecReference& operator= (const T& ref) {
				(*m_Vector)[m_Index] = ref;
				m_Is_Empty = true;
				return *this;
			}

			VecReference& operator+=(const int64_t& rhs) {

				*((size_t*)&(*m_Vector)[m_Index]) += rhs;
				return *this;
			}

			VecReference& operator+=(const uint64_t& rhs) {

				*((size_t*)&(*m_Vector)[m_Index]) += rhs;
				return *this;
			}

			uint64_t GetIndex() { return m_Index; }

			void Reset() {
				m_Index = -1;
				m_Is_Empty = true;
			}

			bool Empty() {
				return m_Is_Empty;
			}
		private:
			std::vector<S>* m_Vector = nullptr;
			uint64_t m_Index;
			bool m_Is_Empty = false;
		};
		
		class ArchiveData {
		public:
			ArchiveData() {}
			ArchiveData(std::vector<char>& data) : m_Data(data) {}
			
			void AddBinaryData(char * data_ptr) {
				size_t offset = 0;
				size_t& Id_size = *((size_t*)data_ptr + offset);
				offset += sizeof(size_t);
				offset += Id_size;
				offset += sizeof(size_t);
				size_t& data_size = *((size_t*)data_ptr + offset);
				offset += sizeof(size_t);
				offset += data_size;

				size_t top = m_Data.size();
				m_Data.resize(m_Data.size() + offset);
				memcpy(m_Data.data() + top, data_ptr, offset);
			}

			void AddBinaryData(BinaryData& data) {
				size_t Binary_size = Utils::CalculateBinarySize(data);

				size_t top = m_Data.size();

				m_Data.resize(m_Data.size() + Binary_size);
				size_t offset = 0;
				memcpy(m_Data.data() + offset, &data.Identifer_Size, sizeof(size_t));
				offset += sizeof(size_t);
				memcpy(m_Data.data() + offset, data.Identifer.data(), data.Identifer.size());
				offset += data.Identifer.size();
				memcpy(m_Data.data() + offset, &data.Size_Tag, sizeof(size_t));
				offset += sizeof(size_t);
				memcpy(m_Data.data() + offset, &data.Data_Size, sizeof(size_t));
				offset += sizeof(size_t);
				memcpy(m_Data.data() + offset, data.Data.data(), data.Data.size());
			}



			void AddIdentifier(std::string& data, bool AddSize = true) {
				if (AddSize) {
					size_t top = m_Data.size();
					m_Data.resize(m_Data.size() + data.size() + sizeof(size_t));
					size_t size_data = data.size();
					memcpy(m_Data.data() + top, &size_data, sizeof(size_t));
					memcpy(m_Data.data() + top + sizeof(size_t), data.data(), data.size());
				} else {
					size_t top = m_Data.size();
					m_Data.resize(m_Data.size() + data.size());
					memcpy(m_Data.data() + top, data.data(), data.size());
				}
			}

			void AddIdentifierSize(size_t size) {
				size_t top = m_Data.size();
				m_Data.resize(m_Data.size() + sizeof(size_t));
				memcpy(m_Data.data() + top , &size, sizeof(size_t));
			}

			VecReference<size_t, char> AddSizeTag(size_t size) {
				size_t top = m_Data.size();
				m_Data.resize(m_Data.size() + sizeof(size_t));
				memcpy(m_Data.data() + top, &size, sizeof(size_t));
				return VecReference<size_t, char>(m_Data, top);
			}

			VecReference<size_t, char> AddData(char* data, size_t size, bool AddSize = false) {
				if (AddSize) {
					size_t top = m_Data.size();
					m_Data.resize(m_Data.size() + size + sizeof(size_t));
					memcpy(m_Data.data() + top, &size, sizeof(size_t));
					memcpy(m_Data.data() + top + sizeof(size_t), data, size);
					return VecReference<size_t, char>(m_Data, top);
				}
				else {
					size_t top = m_Data.size();
					m_Data.resize(m_Data.size() + size);
					memcpy(m_Data.data() + top, data, size);
					return VecReference<size_t, char>(m_Data, top - sizeof(size_t));
				}
			}

			VecReference<size_t, char> AddData(std::vector<char>& data, bool AddSize = false) {
				if (AddSize) {
					size_t top = m_Data.size();
					m_Data.resize(m_Data.size() + data.size() + sizeof(size_t));
					size_t size_data = data.size();
					memcpy(m_Data.data() + top, &size_data, sizeof(size_t));
					memcpy(m_Data.data() + top + sizeof(size_t), data.data(), data.size());
					return VecReference<size_t, char>(m_Data, top);
				}
				else {
					size_t top = m_Data.size();
					m_Data.resize(m_Data.size() + data.size());
					memcpy(m_Data.data() + top, data.data(), data.size());
					return VecReference<size_t, char>(m_Data, top - sizeof(size_t));
				}
			}

			VecReference<size_t, char> AddDataSize(size_t size) {
				size_t top = m_Data.size();
				m_Data.resize(m_Data.size() + sizeof(size_t));
				memcpy(m_Data.data() + top, &size, sizeof(size_t));
				return VecReference<size_t, char>(m_Data, top);
			}

			std::pair<uint32_t, size_t> GetData(std::string& ID, uint32_t serch_offset) {
				size_t offset = serch_offset;

				while (offset < m_Data.size()) {
					size_t& Id_size = *((size_t*)(m_Data.data() + offset));
					offset += sizeof(size_t);

					std::vector<char> Identifier;
					Identifier.resize(Id_size);
					memcpy(Identifier.data(), m_Data.data() + offset, Id_size);
					offset += Id_size;

					offset += sizeof(size_t);

					size_t& Data_size = *((size_t*)(m_Data.data() + offset));
					offset += sizeof(size_t);


					if (std::string(Identifier.begin(), Identifier.end()) == ID) {
						return { offset, Data_size};
					}
					offset += Data_size;

				}

				offset = serch_offset + sizeof(size_t) * 3;


				while (offset < m_Data.size()) {
					size_t& Id_size = *((size_t*)(m_Data.data() + offset));
					offset += sizeof(size_t);

					std::vector<char> Identifier;
					Identifier.resize(Id_size);
					memcpy(Identifier.data(), m_Data.data() + offset, Id_size);
					offset += Id_size;

					offset += sizeof(size_t);

					size_t& Data_size = *((size_t*)(m_Data.data() + offset));
					offset += sizeof(size_t);


					if (std::string(Identifier.begin(), Identifier.end()) == ID) {
						return { offset, Data_size };
					}
					offset += Data_size;

				}
			}


			char* GetArchiveData() {
				return m_Data.data();
			}

			uint64_t GetArchiveSize() {
				return m_Data.size();
			}

			char& operator[] (uint32_t index) {
				return m_Data[index];
			}

		private:
			std::vector<char> m_Data;
		};

		template<typename ArchiveType>
		class OutputArchive {
		public:


			OutputArchive(std::string_view file) : m_FilePath(file) {

			}

			~OutputArchive() {
				Write();
			}

			template<typename T>
			void operator &(T member) {
				if constexpr (is_namevaluepair<T>::value) {
					ProcessBegin();
					Process(member.Name, member.Value);
					ProcessNext();
				}
				else {
					if constexpr (std::is_same<T, BinaryData>::value) {
						std::string a{};
						if (member.Data_Size) {
							m_Size_Ptr.pop_back();
						}

						Process(a, member);
					}
					else {
						ProcessBegin();
						std::string a{};
						Process(a, member);
						ProcessNext();

					}
				}
			}


			void Write() {
				std::fstream file(std::string(m_FilePath), std::ios::out | std::ios::binary);
				file.write(m_Data.GetArchiveData(), m_Data.GetArchiveSize());
				file.close();
			}

			template<typename T>
			void AddClass(NameValuePair<T> Class) {
				*this & Class;
			}

		private:
			template<typename T>
			void Process(std::string& name,  T& value) {
				if constexpr (std::is_class<T>::value && !std::is_same<T, BinaryData>::value) {
					size_t Name_size = name.size();

					if (name.size()) {
						m_Data.AddIdentifier(name);
					}
					else {
						m_Data.AddIdentifierSize(0);
					}

					m_Size_Tag_Ptr = m_Data.AddSizeTag(0);
					m_POD_Size_Ptr = m_Data.AddDataSize(0);

					if (m_Size_Ptr.size() > m_Nested - 1) {
						m_Size_Ptr.pop_back();
					}
					for (auto& ref : m_Size_Ptr) {
						ref += Name_size + sizeof(size_t) * 3;
					}
					m_Size_Ptr.push_back(m_POD_Size_Ptr);


					Process(value, std::integral_constant<bool, std::true_type::value>());
				}
				else {
					Process(NameValuePair<T>{name, value}, std::integral_constant<bool, std::false_type::value>());
				}
			}

			template<typename T>
			void Process(T& value, std::true_type) {
				if constexpr (requires(decltype(*this) & ar, T & v) { Serialize<decltype(*this)>(ar, v); })
				{
					Serialize<decltype(*this)>(* this, value);
				}
				else {
					if constexpr (requires(decltype(*this) & ar, T & v) { v.Serialize(ar); })
					{
						value.Serialize(*this);
					}
				}
			}

			template<typename T>
			void Process(NameValuePair<T> value, std::false_type) {
				BinaryData data;
				if constexpr (!std::is_same<T, BinaryData>::value) {
					data.Identifer = { value.Name.begin(), value.Name.end() };
					data.Identifer_Size = data.Identifer.size();

					const char* bin = reinterpret_cast<const char*>(&value.Value);
					data.Data.reserve(sizeof(T));
					for (int i = 0; i < sizeof(T); i++) {
						data.Data.push_back(bin[i]);
					}

					data.Data_Size = data.Data.size();

				}
				else {
					data = value.Value;
				}
				
				if (m_Nested - 1) {
					if (!value.Name.empty()) {
						m_Data.AddIdentifier(value.Name);
						m_Data.AddSizeTag(data.Size_Tag);
						m_Data.AddDataSize(data.Data_Size);
					}

					if (!m_Size_Tag_Ptr.Empty()) {
						m_Size_Tag_Ptr = data.Size_Tag;
						m_Size_Tag_Ptr.Reset();
					}

					for (auto& ref : m_Size_Ptr) {
						if (!data.Identifer_Size) {
							ref += data.Data_Size;

						}
						else {
							ref += data.Data_Size + data.Identifer_Size + sizeof(size_t) * 3;
						}
					}


					if (!m_POD_Size_Ptr.Empty()) {
						if (!(size_t)m_POD_Size_Ptr) {
							m_POD_Size_Ptr = data.Data_Size;
						}
						m_POD_Size_Ptr.Reset();
					}

					m_Data.AddData(data.Data);
				}
			}

			void ProcessBegin() {
				m_Nested++;

			}

			void ProcessNext() {


				m_Nested--;
			}
			

		private:
			int m_Nested = 0;

			std::vector<VecReference<size_t, char>> m_Size_Ptr;
			VecReference<size_t, char> m_Size_Tag_Ptr;
			VecReference<size_t, char> m_POD_Size_Ptr;

			ArchiveData m_Data;
			std::string_view m_FilePath;
		};

		template<typename ArchiveType>
		class InputArchive {
		public:
			InputArchive(std::string_view FilePath) {
				std::fstream file(std::string(FilePath), std::ios::in | std::ios::binary);
				std::vector<char> buffer(std::istreambuf_iterator<char>(file), {});
				file.close();

				m_Data = buffer;
			}

			template<typename T>
			void operator &(NameValuePair<T> member) {
				ProcessBegin(member.Name);
				Process(member.Name, member.Value);
				ProcessNext();
			}

			template<typename T>
			void operator &(T& member) {
				if constexpr (std::is_same<T, BinaryData>::value) {
					std::string a{};
					Process(a, member);
				}
				else {
					std::string a{};
					Process(a, member);
				}
			}

		private:
			void ProcessBegin(std::string& name) {
				if (!m_Index.size()) {
					auto [Index, Size] = m_Data.GetData(name, 0);
					m_Index.push_back(Index);
					m_CurrentSize = Size;
					m_Nested++;
				}
				else {
					auto [Index, Size] = m_Data.GetData(name, m_Index[m_Index.size() - 1]);
					m_Index.push_back(Index);
					m_CurrentSize = Size;
					m_Nested++;
				}
		
			}

			void ProcessNext() {
				if (!--m_Nested) {
					
				}
				m_Index.pop_back();

			}


			template<typename T>
			void Process(std::string& name, T& value) {
				if constexpr (std::is_class<T>::value && !std::is_same<T, BinaryData>::value) {
					Process(value, std::integral_constant<bool, std::true_type::value>());
				}
				else {
					Process(NameValuePair<T>{name, value}, std::integral_constant<bool, std::false_type::value>());
				}
			}

			template<typename T>
			void Process(T& value, std::true_type) {
				if constexpr (requires(decltype(*this) & ar, T & v) { Deserialize<decltype(*this)>(ar, v); })
				{
					Deserialize<decltype(*this)>(*this, value);
					return;
				}
				else {
					if constexpr (requires(decltype(*this) & ar, T & v) { v.Deserialize(ar); })
					{
						value.Deserialize(*this);
						return;
					}
				}

				if constexpr (requires(decltype(*this) & ar, T & v) { Serialize<decltype(*this)>(ar, v); })
				{
					Serialize<decltype(*this)>(*this, value);
				}
				else {
					if constexpr (requires(decltype(*this) & ar, T & v) { v.Serialize(ar); })
					{
						value.Serialize(*this);
					}
				}
			}

			template<typename T>
			void Process(NameValuePair<T> value, std::false_type) {
				if constexpr (!std::is_same<T, BinaryData>::value) {
					memcpy(&value.Value, &m_Data[m_Index[m_Index.size() - 1]], m_CurrentSize);
				}
				else {
					memcpy(&value.Value.Size_Tag, &m_Data[m_Index[m_Index.size() - 1] - sizeof(size_t) * 2], sizeof(size_t));
					memcpy(&value.Value.Data_Size, &m_Data[m_Index[m_Index.size() - 1] - sizeof(size_t) * 1], sizeof(size_t));
					value.Value.Data.resize(m_CurrentSize);
					memcpy(value.Value.Data.data(), &m_Data[m_Index[m_Index.size() - 1]], m_CurrentSize);
				}
			}

		private:
			int m_Nested = 0;
			std::vector<uint32_t> m_Index;
			uint32_t m_CurrentSize = 0;

			//std::unordered_map<std::string, std::vector<char>> m_DataMap;
			ArchiveData m_Data;
		};

		template<class ArchiveT, typename T, typename... Args>
		static void Serialize_Intrusive(ArchiveT& archive, std::string types_literal, Args&&... args) {
			std::vector<std::string> type_string_literal = Utils::SeparateTypesLiterals(types_literal);

			uint32_t i = 0;
			(Serialize_Member<ArchiveT>(archive, NameValuePair<decltype(args)>{ type_string_literal[i++], args }), ...);
		}

		template<class ArchiveT, typename T>
		static void Serialize_Member(ArchiveT& archive, NameValuePair<T> member) {
			archive & member;
		}

		template<typename T>
		static NameValuePair<T> CreateNVP(std::string name, T& value) {
			return NameValuePair<T>{name, value};
		}

		template<typename T>
		static NameValuePair<T> CreateNVP(T& value) {
			return NameValuePair<T>{ {}, value};
		}
		
		static BinaryData MakeBinaryData(char* data_bin, size_t data_size, size_t size_tag = 0) {
			BinaryData data;
			data.Identifer = {};
			data.Identifer_Size = 0;

			data.Size_Tag = size_tag;

			if (data_bin) {
				data.Data.reserve(data_size);
				for (int i = 0; i < data_size; i++) {
					data.Data.push_back(data_bin[i]);
				}
			}
			data.Data_Size = data_size;
			return data;
		}
	}
}

#define DATA(data, size) Serializer::MakeBinaryData(data, size);
#define DATA(data, size, size_tag) Serializer::MakeBinaryData(data, size, size_tag);
#define MEMBER(member) Alpha::Serializer::CreateNVP(#member, member);
#define CLASS(member) Alpha::Serializer::CreateNVP(#member, member)
#define SERIALIZE(...) \
public:\
template<class Archive>\
void Serialize(Archive& archive) { \
	Alpha::Serializer::Serialize_Intrusive<Archive, decltype(*this)>(archive, #__VA_ARGS__, __VA_ARGS__) ;\
}\
private:\

#include "STDSerialization.h"

