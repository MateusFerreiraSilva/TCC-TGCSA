#include <sys/types.h>
#include "string.h"

#pragma once

const string direct_neighbors_acronym = "dn";

enum class TemporalGraphQueryType {
    DirectNeighbors,
    ReverseNeighbors,
};

class TemporalGraphQuery {
    public:
        TemporalGraphQueryType queryType;
        uint vrtx;
        uint time;

        TemporalGraphQuery(string queryType, uint vrtx, uint time) {
            this->queryType = queryType == direct_neighbors_acronym ? TemporalGraphQueryType::DirectNeighbors : TemporalGraphQueryType::ReverseNeighbors;
            this->vrtx = vrtx;
            this->time = time;
        }
};