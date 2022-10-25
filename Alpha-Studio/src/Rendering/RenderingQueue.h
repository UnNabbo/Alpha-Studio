#pragma once

#include "Core/Core.h"

#include <cstdint>

#include <vector>

#include <functional>

#include "RendererCommand.h"

#define IS_CMD 0x80000000000000;

namespace Alpha {

	class RenderingCommand;

	struct GenericKey {
		uint64_t : 55;
		uint64_t Cmd : 1;
		uint64_t : 8;

		GenericKey() { memset(this, 0, sizeof(GenericKey)); }

		operator uint64_t&() const { return *(uint64_t*)this; }
	};

	struct ObjectKey {
		uint64_t Material : 29;
		uint64_t Depth : 24;
		uint64_t Transparency : 2;

		uint64_t Cmd : 1;

		uint64_t ViewportLayer : 3;
		uint64_t Viewport : 3;
		uint64_t Layer : 2;


		ObjectKey() { memset(this, 0, sizeof(ObjectKey)); }

		operator uint64_t& () const { return *(uint64_t*)this; }
	};

	struct CommandKey {
		uint64_t Command : 55;

		uint64_t Cmd : 1;

		uint64_t ViewportLayer : 3;
		uint64_t Viewport : 3;
		uint64_t Layer : 2;


		CommandKey() { memset(this, 0, sizeof(CommandKey)); }

		operator uint64_t& () const { return *(uint64_t*)this; }
	};



	class RenderingQueue {
	public:
		RenderingQueue();
		~RenderingQueue();

		void Execute();

		void SubmitObject(Reference<RenderingCommand> cmd, ObjectKey key);
		void SubmitCommand(Reference<RenderingCommand> cmd);

		void Clear();
	private:
		void Sort();

	private:
		std::vector< std::pair<uint64_t, Reference<RenderingCommand> > > CommandQueue;
	};
}