/**
* CLASS: VacuumAgent
* DATE: 25/04/16
* AUTHOR: Kyle Morris
* DESCRIPTION: Simple reflex agent to run in a basic 2x1 Vacuum environment.
*/

#ifndef MORRIS_AIMA_VACUUMAGENT_H
#define MORRIS_AIMA_VACUUMAGENT_H

#include <Agent.h>
#include "VacuumAgent.h"
class SimpleReflexVacuumAgent : public VacuumAgent {

public:
    virtual std::string toString() override;
    virtual std::string getType() override;
    virtual Action *think(Percept *given) override;
};

#endif //MORRIS_AIMA_VACUUMAGENT_H
