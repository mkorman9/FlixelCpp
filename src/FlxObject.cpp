#include "FlxObject.h"
#include "backend/BackendHolder.h"
#include "FlxGroup.h"

FlxObject::FlxObject() {
    entityType = FLX_OBJECT;
    collidate = true;

    visible = true;
    x = y = angle = angularVelocity = 0.f;
    width = height = 0;
    color = 0xffffff;
    alpha = 1.0f;

    maxVelocity.x = 1000;
    maxVelocity.y = 1000;
}


void FlxObject::update() {
    if(!active) return;

    float dt = BackendHolder::get().getBackend()->getDeltaTime();

    x += velocity.x * dt;
    y += velocity.y * dt;
    velocity.x += acceleration.x;
    velocity.y += acceleration.y;

    angle += angularVelocity * dt;

    if(velocity.x > maxVelocity.x) velocity.x = maxVelocity.x;
    if(velocity.y > maxVelocity.y) velocity.y = maxVelocity.y;
    if(velocity.x < -maxVelocity.x) velocity.x = -maxVelocity.x;
    if(velocity.y < -maxVelocity.y) velocity.y = -maxVelocity.y;

    hitbox.x = x + hitboxMove.x;
    hitbox.y = y + hitboxMove.y;
}


FlxVector FlxObject::getCenter() {
    return FlxVector(x + (width / 2), y + (height / 2));
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

    FlxObject *col1 = (FlxObject*)obj1.overlaps(floor);
    FlxObject *col2 = (FlxObject*)obj2.overlaps(floor);

    return (col1 && col1->collidate) || (col2 && col2->collidate);
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

    FlxObject *col1 = (FlxObject*)obj1.overlaps(ceil);
    FlxObject *col2 = (FlxObject*)obj2.overlaps(ceil);

    return (col1 && col1->collidate) || (col2 && col2->collidate);
}


FlxBasic* FlxObject::overlaps(FlxBasic *object) {

    if(object->entityType == FLX_OBJECT) {
        if(hitbox.overlaps(((FlxObject*)object)->hitbox)) return object;
    }
    else if(object->entityType == FLX_GROUP) {
        FlxGroup *group = (FlxGroup*) object;

        for(unsigned int i = 0; i < group->members.size(); i++) {
            FlxBasic *obj = overlaps(group->members[i]);
            if(obj != NULL) return obj;
        }
    }

    return NULL;
}


FlxBasic* FlxObject::collide(FlxBasic *object) {

    if(!collidate) return NULL;

    if(object->entityType == FLX_OBJECT) {
        bool col = false;
        FlxObject *obj = (FlxObject*) object;
        float dt = BackendHolder::get().getBackend()->getDeltaTime();

        if(!obj->collidate) return NULL;

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

        return col ? object : NULL;
    }
    else if(object->entityType == FLX_GROUP) {
        FlxGroup *group = (FlxGroup*) object;
        FlxBasic *ent = 0;

        for(int i = group->members.size() - 1; i >= 0; i--) {
            ent = collide(group->members[i]);
        }

        return ent;
    }

    return 0;
}


void FlxObject::draw() {
}
