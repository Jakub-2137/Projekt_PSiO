#include "player_class.h"
#include "hitbox.h"

extern float acceleration;
extern float max_gravity;

Player_class::Player_class(float x_, float y_, float w_, float h_, sf::Texture &tex){

    health = 350;

    face_right = true;
    dead = false;
    got_him = false;
    attacking = false;

    size.x = w_;
    size.y = h_;

    walk_counter = 0;
    repose_counter = 0;
    attack_counter = 0;

    walk_frames = 4;
    repose_frames = 4;
    attack_frames = 4;

    walk_speed = 14;
    repose_speed = 20;
    attack_speed = 10;

    jump_height = 7.f;
    speed = 5.f;

    frame_size.x = 143;
    frame_size.y = 151;

    frames_amount.x = tex.getSize().x / frame_size.x;
    frames_amount.y = tex.getSize().y / frame_size.y;

    for(int y = 0; y < frames_amount.y; y++){
        for(int x = 0; x < frames_amount.x; x++){
            sf::IntRect frame(x * frame_size.x, y * frame_size.y, frame_size.x, frame_size.y);
            anim_frames.emplace_back(frame);
        }
    }
    setTextureRect(anim_frames[0]);
    setTexture(tex);
    setPosition(x_,y_);
}

void Player_class::update(bool &key_space,bool &key_a, bool &key_d, bool &mouse_left, std::vector<Platform_class> &level){

    if(key_space && on_ground)
        velocity.y = -std::abs(jump_height);
    if(on_ground == false){
        velocity.y += acceleration;
        if(velocity.y > max_gravity)
            velocity.y = max_gravity;
    }
    if(key_a){
        face_right = false;
        velocity.x = -1.f;
    }
    if(key_d){
        face_right = true;
        velocity.x = 1.f;
    }
    if(!(key_a || key_d))
        velocity.x = 0.f;

    move(velocity.x * speed,0);
    collide(velocity.x, 0.f, level);

    on_ground = false;

    move(0, velocity.y);
    collide(0.f, velocity.y, level);

    animate(mouse_left);
}

void Player_class::collide(float x_vel, float y_vel, std::vector<Platform_class> &level){
    for(auto &a : level){
        if(getPosition().x + 45.f < a.hitbox.right &&
           getPosition().x + size.x - 35.f > a.hitbox.left &&
           getPosition().y + 5.f < a.hitbox.bottom &&
           getPosition().y + size.y - 5.f > a.hitbox.top)
        {
            collision = true;
        }
        else{
            collision = false;
        }
        if(collision){
            if(x_vel > 0){
                setPosition(a.hitbox.left - size.x + 35.f, getPosition().y);
                velocity.x = 0.f;
            }
            if(x_vel < 0){
                setPosition(a.hitbox.right - 45.f, getPosition().y);
                velocity.x = 0.f;
            }
            if(y_vel > 0){
                setPosition(getPosition().x, a.hitbox.top - size.y + 5.f); //+1.f
                velocity.y = 0.f;
                on_ground = true;
            }
            if(y_vel < 0){
                setPosition(getPosition().x, a.hitbox.bottom - 5.f);
                velocity.y = 0.f;
            }
        }
    }
}

void Player_class::animate(bool &mouse_left){
    attack(mouse_left);
    if(std::abs(velocity.x) > 0)
        walk();
    else
        repose();
}

void Player_class::walk(){
    for(int i = 0; i < walk_frames; i++){
        if(walk_counter == (i + 1) * walk_speed){
            if(face_right == true){
                setTextureRect(anim_frames[i]);
            } else{
                setTextureRect(anim_frames[i + 8]);
            }
        }
    }
    if(walk_counter == walk_frames * walk_speed){
        walk_counter = 0;
    }
    walk_counter++;
}

void Player_class::repose(){
    for(int i = 0; i < repose_frames; i++){
        if(repose_counter == (i + 1) * repose_speed){
            if(face_right == true){
                setTextureRect(anim_frames[i + walk_frames]);
            } else{
                setTextureRect(anim_frames[i + 12]);
            }
        }
    }
    if(repose_counter == repose_frames * repose_speed){
        repose_counter = 0;
    }
    repose_counter++;
}

void Player_class::attack(bool &mouse_left){
    if(mouse_left){
        for(int i = 0; i < attack_frames; i++){
            if(attack_counter == (i + 1) * attack_speed){
                if(face_right){
                    setTextureRect(anim_frames[i + 16]);
                } else{
                    setTextureRect(anim_frames[i + 20]);
                }
            }
        }
        if(attack_counter == attack_frames * attack_speed){
            attack_counter = 0;
        }
        attack_counter++;

        attacking = true;
    }
    else{
        attacking = false;
    }
}





