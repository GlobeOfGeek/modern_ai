#include "VacuumEnvironment.h"
#include <VacuumPercept.h>
#include "RandomReflexVacuumAgent.h"
#include "Entity.h"
#include "VacuumEnvironmentState.h"
#include "TileEnvironmentState.h"
#include "SimpleReflexVacuumAgent.h"
#include <vector>
#include <DirtEntity.h>
#include <WallEntity.h>

VacuumEnvironmentState::VacuumEnvironmentState(int width, int height) : TileEnvironmentState(width, height) {

}

bool VacuumEnvironmentState::cleanTile() {
    VacuumAgent *agent = findVacuum();
    TileLocation *vacLocation = getLocationOf(agent->getId());
    DirtEntity *found; //the dirt we found, and need to clean
    std::vector<Entity *> entities;
    bool result = false;

    if(isDirty(vacLocation->getX(), vacLocation->getY())) {
        entities = getEntitiesAt(vacLocation);
        //traverse all entities on tile and find dirt
        for(vector<Entity *>::iterator it = entities.begin(); it != entities.end(); ++it) {
            Entity *current = (*it);
            DirtEntity *dirt = dynamic_cast<DirtEntity *>(current);
            if (dirt != NULL) { //we found the dirt
                found = dirt;
                result = true;
            }
        }
    }

    remove(found->getId()); //remove the dirt we found
}

bool VacuumEnvironmentState::hasWall(int x, int y) {
    TileLocation *tile = new TileLocation(x, y);
    bool found = false;
    vector<Entity *> entities = getEntitiesAt(tile);

    //traverse all entities on tile and find dirt
    for(vector<Entity *>::iterator it = entities.begin(); it != entities.end(); ++it) {
        Entity *current = (*it);
        WallEntity *wall = dynamic_cast<WallEntity *>(current);
        if(wall!=NULL) { //we found the dirt
            found = true;
        }
    }

    delete tile;
    return found;
}

bool VacuumEnvironmentState::moveVacuum(int x, int y) {
    VacuumAgent *vacuum = findVacuum();
    TileLocation *targetLocation = new TileLocation(x, y);
    bool result = false;
    if(vacuum!=NULL) {
        //only move if we're within environment bounds
        if(x>=0 && x <this->getWidth() && y>=0 && y<this->getHeight()) {
            if (moveEntity(vacuum->getId(), targetLocation)) {
                result = true;
            }
        }
    }
    delete targetLocation;
    return result;
}

VacuumAgent *VacuumEnvironmentState::findVacuum() {
    VacuumAgent *found = NULL;
    std::vector<Entity *> entities = TileEnvironmentState::getEntities();

    //traverse all entities in environment and find the vacuum.
    for(std::vector<Entity *>::iterator it = entities.begin(); it != entities.end(); ++it) {
        Entity *current = (*it);
        if(dynamic_cast<SimpleReflexVacuumAgent *>(current)!=NULL) { //we found the agent
            found = dynamic_cast<SimpleReflexVacuumAgent *>(current);
        } else if(dynamic_cast<RandomReflexVacuumAgent *>(current) != NULL) { //we found the agent
            found = dynamic_cast<RandomReflexVacuumAgent *>(current);
        }
    }

    return found;
}

//TODO these general isDirty and findVacuum are almost identical. Make some more helpful methods in superclass for locating entities of given type, and test those.
bool VacuumEnvironmentState::isDirty(int x, int y) {
    TileLocation *tile = new TileLocation(x, y);
    bool found = false;
    vector<Entity *> entities = getEntitiesAt(tile);

    //traverse all entities on tile and find dirt
    for(vector<Entity *>::iterator it = entities.begin(); it != entities.end(); ++it) {
        Entity *current = (*it);
        DirtEntity *dirt = dynamic_cast<DirtEntity *>(current);
        if(dirt!=NULL) { //we found the dirt
            found = true;
        }
    }

    delete tile;
    return found;
}