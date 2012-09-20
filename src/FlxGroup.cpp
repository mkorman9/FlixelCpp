#include "FlxGroup.h"
#include "FlxObject.h"

FlxGroup::FlxGroup() {
    entityType = FLX_GROUP;
}


FlxGroup::~FlxGroup() {
    clear();
}


FlxBasic* FlxGroup::add(FlxBasic *object) {

    if(object) {
        object->scroolFactor = scroolFactor;
        members.push_back(object);
    }

    return object;
}


bool FlxGroup::remove(FlxBasic *object, bool dontDelete) {

    if(!object) return false;

    for(unsigned int i = 0; i < members.size(); i++) {
        if(members[i] == object) {

            if(!dontDelete) {
                delete members[i];
                members[i] = NULL;
            }

            members.erase(members.begin() + i);
            return true;
        }
    }

    return false;
}


void FlxGroup::clear() {
    for(unsigned int i = 0; i < members.size(); i++) {
        delete members[i];
        members.erase(members.begin());
    }
}


void FlxGroup::update() {

    for(unsigned int i = 0; i < members.size(); i++) {
        if(members[i]) members[i]->update();
    }
}


void FlxGroup::drawGUI() {
    for(unsigned int i = 0; i < members.size(); i++) {
        if(members[i]) {
            if(members[i]->entityType == FLX_OBJECT) {
                FlxObject *obj = (FlxObject*) members[i];
                if(obj->isGUI) obj->draw();
            }
            else {
                FlxGroup *group = (FlxGroup*) members[i];
                group->drawGUI();
            }
        }
    }
}


void FlxGroup::draw() {

    for(unsigned int i = 0; i < members.size(); i++) {
        if(members[i]) {
            if(members[i]->entityType == FLX_OBJECT) {
                FlxObject *obj = (FlxObject*) members[i];
                if(!obj->isGUI) obj->draw();
            }
            else {
                FlxGroup *group = (FlxGroup*) members[i];
                group->draw();
            }
        }
    }
}


FlxBasic* FlxGroup::overlaps(FlxBasic *object, const CollisionCallback& callback) {

    if(object->entityType == FLX_OBJECT) {
        return object->overlaps(this, callback);
    }
    else if(object->entityType == FLX_GROUP) {
        FlxGroup *group = (FlxGroup*) object;

        for(unsigned int i = 0; i < group->members.size(); i++) {
            if(overlaps(group->members[i], callback)) return group->members[i];
        }
    }

    return NULL;
}


FlxBasic* FlxGroup::collide(FlxBasic *object, const CollisionCallback& callback) {

    if(object->entityType == FLX_OBJECT) {
        FlxBasic *ent = NULL;

        for(int i = members.size() - 1; i >= 0; i--) {
            FlxObject *obj = (FlxObject*)members[i];
            ent = obj->collide(object, callback);
        }

        return ent;
    }
    else if(object->entityType == FLX_GROUP) {
        FlxGroup *group = (FlxGroup*)object;
        FlxBasic *ent = NULL;

        for(int i = members.size() - 1; i >= 0; i--) {
            for(int j = group->members.size() - 1; j >= 0; j--) {
                ent = members[i]->collide(group->members[j], callback);
            }
        }

        return ent;
    }

    return NULL;
}


FlxGroup::EntitiesSet FlxGroup::selfOverlaps(const CollisionCallback& callback) {
    FlxGroup::EntitiesSet set = { 0, 0 };

    for(unsigned int i = 0; i < members.size(); i++) {
        for(int j = members.size() - 1; j >= 0; j--) {
            if((members[i] != members[j]) && members[i]->overlaps(members[j])) {
                set.first = members[i];
                set.second = members[j];

                if(callback != nullptr) callback(set.first, set.second);
            }
        }
    }

    return set;
}


FlxGroup::EntitiesSet FlxGroup::selfCollide(const CollisionCallback& callback) {
    FlxGroup::EntitiesSet set = { 0, 0 };

    for(unsigned int i = 0; i < members.size(); i++) {
        for(int j = members.size() - 1; j >= 0; j--) {
            if((members[i] != members[j]) && members[i]->collide(members[j])) {
                set.first = members[i];
                set.second = members[j];

                if(callback != nullptr) callback(set.first, set.second);
            }
        }
    }

    return set;
}

