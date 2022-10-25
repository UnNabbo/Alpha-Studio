#include "RenderingQueue.h"

#include <algorithm>

#include "RenderCommandFn.h"

namespace Alpha {
	RenderingQueue::RenderingQueue(){
		CommandQueue.reserve(1024 * 10);
	}

	RenderingQueue::~RenderingQueue(){

	}

	void RenderingQueue::SubmitObject(Reference<RenderingCommand> cmd, ObjectKey key){
		CommandQueue.push_back({key, cmd});
	}

	void RenderingQueue::SubmitCommand(Reference<RenderingCommand> cmd){

	}


	void RenderingQueue::Execute(){
		std::sort(CommandQueue.begin(), CommandQueue.end());
		for (auto [_, Command] : CommandQueue) {
			Command->Execute();
		}
		CommandQueue.clear();
	}

	void RenderingQueue::Clear(){
		CommandQueue.clear();
	}

	void RenderingQueue::Sort(){
		std::sort(CommandQueue.begin(), CommandQueue.end());
	}
}