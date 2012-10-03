#include "FlxObject.h"
#include "FlxGroup.h"
#include "FlxG.h"

FlxObject::FlxObject() {
    entityType = FLX_OBJECT;
    collisions = true;

    visible = true;
    x = y = angle = angularVelocity = 0.f;
    width = height = 0;
    color = 0xffffff;
    alpha = 1.0f;
    scale.x = scale.y = 1;

    maxVelocity.x = 1000.f;
    maxVelocity.y = 1000.f;

    isGUI = false;

    isFollowingPath = false;
    followingVelocity = 1.f;
    pathToFollow = NULL;
}


FlxObject::~FlxObject() {
}


void FlxObject::update() {
    if(!active) return;

    float dt = FlxG::fixedTime;

    if(!isFollowingPath) {
        x += velocity.x * dt;
        y += velocity.y * dt;
        velocity.x += acceleration.x * dt;
        velocity.y += acceleration.y * dt;

        if(velocity.x > maxVelocity.x) velocity.x = maxVelocity.x;
        if(velocity.y > maxVelocity.y) velocity.y = maxVelocity.y;
        if(velocity.x < -maxVelocity.x) velocity.x = -maxVelocity.x;
        if(velocity.y < -maxVelocity.y) velocity.y = -maxVelocity.y;
    }
    else {
        if(pathToFollow) {
            if((float)std::floor(x) == currentNode.x && (float)std::floor(y) == currentNode.y) {
                if(pathToFollow->isEnd()) {
                    stopFollowing();
                }
                else {
                    currentNode = pathToFollow->getNextNode();
                }
            }
            else {
                FlxVector vec(x, y, currentNode.x, currentNode.y);
                vec.normalize();

                x += vec.x * followingVelocity * dt;
                y += vec.y * followingVelocity * dt;
            }
        }
    }

    angle += angularVelocity * dt;

    hitbox.x = x + hitboxMove.x;
    hitbox.y = y + hitboxMove.y;
}


FlxVector FlxObject::getCenter() {
    return FlxVector(x + (width / 2), y + (height / 2));
}


void FlxObject::kill() {
    visible = false;
    FlxBasic::kill();
}


bool FlxObject::isTouchingFloor(FlxBasic *floor) {

    FlxObject obj1;
    obj1.hitbox.width = 1;
    obj1.hitbox.height = 1;
    obj1.hitbox.x = x;
    obj1.hitbox.y = y + height + 3;

    FlxObject obj2;
    obj2.hitbox.width = 1;
    obj2.hitbox.height = 1;
    obj2.hitbox.x = x + width;
    obj2.hitbox.y = y + height + 3;

    FlxObject obj3;
    obj3.hitbox.width = 1;
    obj3.hitbox.height = 1;
    obj3.hitbox.x = x + (width / 2);
    obj3.hitbox.y = y + height + 3;

    FlxObject *col1 = (FlxObject*)obj1.overlaps(floor);
    FlxObject *col2 = (FlxObject*)obj2.overlaps(floor);
    FlxObject *col3 = (FlxObject*)obj3.overlaps(floor);

    return (col1 && col1->collisions) || (col2 && col2->collisions) || (col3 && col3->collisions);
}


bool FlxObject::isTouchingCeiling(FlxBasic *ceil) {

    FlxObject obj1;
    obj1.hitbox.width = 1;
    obj1.hitbox.height = 1;
    obj1.hitbox.x = x;
    obj1.hitbox.y = y - 3;

    FlxObject obj2;
    obj2.hitbox.width = 1;
    obj2.hitbox.height = 1;
    obj2.hitbox.x = x + width;
    obj2.hitbox.y = y - 3;

    FlxObject obj3;
    obj3.hitbox.width = 1;
    obj3.hitbox.height = 1;
    obj3.hitbox.x = x + (width / 2);
    obj3.hitbox.y = y - 3;

    FlxObject *col1 = (FlxObject*)obj1.overlaps(ceil);
    FlxObject *col2 = (FlxObject*)obj2.overlaps(ceil);
    FlxObject *col3 = (FlxObject*)obj3.overlaps(ceil);

    return (col1 && col1->collisions) || (col2 && col2->collisions) || (col3 && col3->collisions);
}


FlxBasic* FlxObject::overlaps(FlxBasic *object, const CollisionCallback& callback) {

    if(object->entityType == FLX_OBJECT) {
        if(hitbox.overlaps(((FlxObject*)object)->hitbox)) {
            if(callback != nullptr) callback(this, object);
            return object;
        }
    }
    else if(object->entityType == FLX_GROUP) {
        FlxGroup *group = (FlxGroup*) object;
        FlxBasic *mem = NULL;

        for(unsigned int i = 0; i < group->members.size(); i++) {
            FlxBasic *obj = overlaps(group->members[i]);
            if(obj != NULL) {
                if(callback != nullptr) callback(this, group->members[i]);
                mem = obj;
            }
        }

        return mem;
    }

    return NULL;
}


FlxBasic* FlxObject::collide(FlxBasic *object, const CollisionCallback& callback) {

    if(!collisions) return NULL;

    if(object->entityType == FLX_OBJECT) {
        bool col = false;
        FlxObject *obj = (FlxObject*) object;
        float dt = FlxG::fixedTime;

        if(!obj->collisions) return NULL;

        // x-axis
        FlxRect rect1;
        rect1.x = hitbox.x + (velocity.x * dt);
        rect1.y = hitbox.y;
        rect1.width = hitbox.width;
        rect1.height = hitbox.height;

        if(rect1.overlaps(obj->hitbox)) {
            velocity.x = 0;
            col = true;
        }

        // y-axis
        FlxRect rect2;
        rect2.x = hitbox.x;
        rect2.y = hitbox.y + (velocity.y * dt);
        rect2.width = hitbox.width;
        rect2.height = hitbox.height;

        if(rect2.overlaps(obj->hitbox)) {
            velocity.y = 0;
            col = true;
        }

        if(col && callback != nullptr) callback(this, object);
        return col ? object : NULL;
    }
    else if(object->entityType == FLX_GROUP) {
        FlxGroup *group = (FlxGroup*) object;
        FlxBasic *ent = 0;

        for(int i = group->members.size() - 1; i >= 0; i--) {
            ent = collide(group->members[i], callback);
        }

        return ent;
    }

    return 0;
}


void FlxObject::followPath(FlxPath *toFollow, float speed) {
    if(!toFollow) return;

    pathToFollow = toFollow;
    followingVelocity = speed;
    isFollowingPath = true;

    pathToFollow->setFront();

    if(pathToFollow->isEnd()) {
        stopFollowing();
    }
    else {
        currentNode = pathToFollow->getNextNode();
    }
}


void FlxObject::stopFollowing() {
    pathToFollow = NULL;
    isFollowingPath = false;
}


void FlxObject::draw() {
}
