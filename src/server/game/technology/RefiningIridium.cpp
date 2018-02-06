//
// Created by Guillaume on 06/02/2018.
//

#include "RefiningIridium.hh"
#include "../building/ResearchCenter.hh"

bl::server::game::technology::RefiningIridium::RefiningIridium() :
		ATechnology(
				RefiningIridium::id,
				"Refining iridium",
				"Develop new refining technique to extract iridium from iron. Allow to build an iridium refinery",
				{},
				{{building::ResearchCenter::id, 1}},
				600
		) {
}

