//
// Created by Иван Ильин on 14.03.2021.
//

#include "Player.h"
#include "engine/utils/Log.h"

Player::Player() : RigidBody(Mesh::Cube(ObjectNameTag("Player"), 3)) {
    setCollider(true);
    setCollision(true);
    setColor(sf::Color(240, 168, 168));
    scale(Vec3D(1, 1.8, 1));
    setAcceleration(Vec3D(0, -MinecraftConsts::GRAVITY, 0));
    setVisible(false);
}

void Player::nextBlock() {
    _selectedBlock = Cube::Type(((int)_selectedBlock + 1) % (int)Cube::Type::none);
}

void Player::previousBlock() {
    if((int)_selectedBlock > 0) {
        _selectedBlock = Cube::Type(((int)_selectedBlock - 1) % (int)Cube::Type::none);
    } else {
        _selectedBlock = Cube::Type((int)Cube::Type::none - 1);
    }
}

void Player::collisionCallBack(const CollisionInfo &info) {
    // setting vertical velocity to zero after collision

    Vec3D velocity_parallel = info.normal * velocity().dot(info.normal);
    Vec3D velocity_perpendicular = velocity() - velocity_parallel;

    if (velocity().dot(info.normal) > 0) {
        setVelocity(velocity_perpendicular);
    }
}
