#ifndef SOLDIERAPP_RANKREPOSITORY_H
#define SOLDIERAPP_RANKREPOSITORY_H

#include <list>
#include "RankDescription.h"

/**
 * Class that contains prepared list of RankDescription
 */
class RankRepository {
public:
    RankRepository();

    /**
     *
     * @return prepared list of RankDescription
     */
    const std::list<RankDescription> &getRanks() const;

private:
    std::list<RankDescription> ranks;
};

#endif //SOLDIERAPP_RANKREPOSITORY_H
