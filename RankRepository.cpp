//
// Created by pawlllosss on 18.03.2020.
//

#include "RankRepository.h"

RankRepository::RankRepository() {
    ranks.push_front(RankDescription("Captain", CAPTAIN));
    ranks.push_front(RankDescription("Lieutenant", LIEUTENANT));
    ranks.push_front(RankDescription("Sergeant", SERGEANT));
    ranks.push_front(RankDescription("Corporal", CORPORAL));
    ranks.push_front(RankDescription("Private", PRIVATE));
}

const std::list<RankDescription> &RankRepository::getRanks() const {
    return ranks;
}
