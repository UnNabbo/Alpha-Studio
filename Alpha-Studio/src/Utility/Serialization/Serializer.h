#pragma once

#include <string>
#include "Core/Core.h"
#include <typeinfo>   



namespace Alpha {
	namespace Utils {
		
	}

	class OutputArchive {
	public:
		template<typename T>
		void operator &(T& memb) {

		}


	};

	class InputArchive {


		template<typename T>
		void operator &(T& memb) {

		}
	};

	class Serializer {
	public:
		template<typename type, typename... Args>
		static void Serialize_Intrusive(std::string type_literal, std::string types_literal, Args&&... args) {
			ALPHA_TRACE("{}({})", type_literal, sizeof(type));

			types_literal.erase(remove(types_literal.begin(), types_literal.end(), ' '), types_literal.end());
			std::vector<std::string> type_string_literal;
			uint32_t offset = 0;
			while (true) {
				size_t index = types_literal.find(',', offset);
				if (index != std::string::npos) {
					type_string_literal.push_back(types_literal.substr(offset, index));
					offset = index + 1;
				} else {
					type_string_literal.push_back(types_literal.substr(offset, types_literal.length()));
					break;
				}
			}
			uint32_t i = 0;
			(Serialize_Member(type_string_literal[i++], args), ... );
		}

		template<typename type>
		static void Serialize_Member(std::string type_literal, type& member) {
			std::string type_name = typeid(type).name();
			if constexpr (std::is_pointer<type>::value) {
				ALPHA_TRACE("{}({}) {}: {}", type_name, sizeof(member), type_literal, *member);
				return;
			}

			if constexpr (std::is_class<type>::value) {
				ALPHA_TRACE("{}({}) {}", type_name, sizeof(member), type_literal);
				Serialize<type>(member);
				return;
			}

			ALPHA_TRACE("{}({}) {}", type_name, sizeof(member), type_literal);
		}

		template<typename type>
		static type* Deserialize(void * ptr) {
			auto class_ptr = new (ptr)type;
			
		}

	

	public:


		template<typename T>
		struct HasSerialize
		{
			template<typename U, void(U::*)()> struct SFINAE {};
			template<typename U> static char Test(SFINAE<U, &U::Serialize>*);
			template<typename U> static int Test(...);
			static const bool Has = sizeof(Test<T>(0)) == sizeof(char);
		};

		template<typename Type>
		static void CallSerialize(Type& m, std::true_type)
		{
			m.Serialize();
		}
		template<typename Type>
		static void CallSerialize(Type&, std::false_type)
		{

		}
		template<typename Type>
		static void CallSerialize(Type& m)
		{
			CallSerialize(m, std::integral_constant<bool, HasSerialize<Type>::Has>());
		}


	};


	template<class Archive>
	static void Serialize(Archive& archive) {
		archive &;
	}

}

#define SERIALIZE(type, ...) void Serialize() { Alpha::Serializer::Serialize_Intrusive<type>(#type, #__VA_ARGS__, __VA_ARGS__) ; }

namespace Alpha {

	struct MeshData;
	class AB {
	private:
		int xilofone = 12;
		std::vector<int> kassante;


		void v() {

		}
	public:
		template<class Archive>
		static void Serialize(Archive& archive) {
			archive & xilofone;
			archive & kassante;
		}

		SERIALIZE(AB, xilofone, kassante)
	};


	void test() {
		AB a;
		Serialize(a);
	}
}