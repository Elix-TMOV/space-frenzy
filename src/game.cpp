#include "game.hpp"

std::vector<SpaceShip> Game::aliens;
std::list<Bullets> Game::bullets;
std::list<Bullets> Game::playerBullets;
std::list<Explosion> Game::activeExplosions;

// std::cout << "Player initialized at position: " << Game::pla5yer.position.x << ", " << Game::player.position.y << std::endl;
Game::Game(): player({200, 500}) {
    aliens.push_back(SpaceShip({500, 100}, 1));
    aliens.push_back(SpaceShip({500, 100}, 3));
    aliens.push_back(SpaceShip({500, 100}, 3));
    aliens.push_back(SpaceShip({700, 100}, 2));
}

void Game::update() {
    player.update();
    for (auto& alien : aliens) {
        if (alien.hp > 0) {
            alien.update();
        }
    }
    for (auto it = bullets.begin(); it != bullets.end();) {
        it->update();
        bool collision = CheckCollisionCircles(it->position, 20.0f, player.position, 50.0f);
        if (collision) {
            player.hp -= 1;
        }
        if (it->destroyed || collision) {
            it = bullets.erase(it);
            // cout << bullets.size() << endl;
        } else {
            it++;
        }
    }
    for (auto it = playerBullets.begin(); it != playerBullets.end();) {
        it->update();
        bool collision = false;
        if (it->explosive == false) {
            for (auto& alien: aliens) {
                Circle circleCollider = alien.getCollider();
                collision = CheckCollisionCircles(circleCollider.center, circleCollider.radius, it->position, 20);
                if (collision == true) {
                    alien.hp -= 1;
                    break;
                }
            }
        }
        else {
            for (auto& alien: aliens) {
                Circle circleCollider = alien.getCollider();
                collision = CheckCollisionCircles(circleCollider.center, circleCollider.radius, it->position, 20);
                if (collision == true) {
                    alien.hp-=3;
                    for (auto& otherAlien: aliens) {
                        Circle circleCollider = otherAlien.getCollider();
                        bool blastCollision =  CheckCollisionCircles(circleCollider.center, circleCollider.radius, it->position, 500);
                        if (blastCollision) {
                            otherAlien.hp -= 3;
                            it->collided();
                        }
                    }
                    break;
                }
            }
        }
        if (it->destroyed || collision) {
            it = playerBullets.erase(it);
        } else {
            it++;
        }
    }
    // Uncomment and define boss if needed
    // boss.update(player.position, player.sentinalIdleSprite.width / 12, player.sentinalIdleSprite.height / 6);
}

void Game::draw() {
    player.draw();
    char hpText[3];
    sprintf(hpText, "%d", player.hp);
    DrawText(hpText, 10, 10, 50, RED); 
    for (auto& alien : aliens) {
        if (alien.hp > 0) {
            alien.draw();
        }
    }
    for (auto& bullet: bullets) {
        bullet.draw();
    }
    for (auto& playerBullet: playerBullets) {
        playerBullet.draw();
    }
    for (auto& explosion: activeExplosions) {
        // if (explosion.isActive() = true) {
        //     explosion.draw();
        // }
        if (explosion.isActive() == true) {
            explosion.draw();
        }
    }

    // Uncomment and define boss if needed
    // boss.draw();
}

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

Vector2 Game::getPlayerPosition() {
    return getInstance().player.position;
}

void Game::addBullet(Bullets bullet){
    bullets.push_back(bullet);
}

void Game::addPlayerBullet(Bullets bullet) {
    playerBullets.push_back(bullet);  
}

void Game::addActiveExplosion(Explosion ex) {
    activeExplosions.push_back(ex);
}