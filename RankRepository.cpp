//
// Created by pawlllosss on 18.03.2020.
//

#include "RankRepository.h"

RankRepository::RankRepository() {
    ranks.push_front(Rank("Captain"));
    ranks.push_front(Rank("Lieutenant"));
    ranks.push_front(Rank("Sergeant"));
    ranks.push_front(Rank("Corporal"));
    ranks.push_front(Rank("Private"));
}

const std::list<Rank> &RankRepository::getRanks() const {
    return ranks;
}
