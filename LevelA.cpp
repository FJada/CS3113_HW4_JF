#include "LevelA.h"
#include "Utility.h"
#include "Map.h"
#include "Entity.h"
#include "Scene.h"

#define LEVEL_WIDTH 29
#define LEVEL_HEIGHT 8
/**
* Author: JADA FORRESTER
* Assignment: Rise of the AI
* Date due: 2023-11-18, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/


unsigned int LEVELA_DATA[] =
{
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 2, 2, 2, 0,
    3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 0, 2, 0, 2, 0, 2, 0, 2, 2, 2, 2, 2, 1,
    3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 0, 2, 0, 2, 0, 2, 2, 2, 2, 2, 2,
};

LevelA::~LevelA()
{
    delete[] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeMusic(m_state.bgm);
}

void LevelA::initialise()
{
    m_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("assets/bricks.png");
    GLuint enemy_texture_id_1 = Utility::load_texture("assets/heartless_1.png");
    GLuint enemy_texture_id_2 = Utility::load_texture("assets/heartless_3.png");
    GLuint enemy_texture_id_3 = Utility::load_texture("assets/heartless_2.png");
    GLuint projectile_texture_id_1 = Utility::load_texture("assets/firee_ball.png");

    

    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_DATA, map_texture_id, 1.0f, 4, 1);
    
    // Code from main.cpp's initialise()
    /**
     */
    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(1.0f, 0.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(2.5f);
    m_state.player->set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    m_state.player->m_texture_id = Utility::load_texture("assets/sora.png");
    
    // Walking
    m_state.player->m_walking[m_state.player->LEFT]   = new int[3] { 4, 5, 6,};
    m_state.player->m_walking[m_state.player->RIGHT]  = new int[3] { 7, 8, 9};
    m_state.player->m_walking[m_state.player->UP]     = new int[3] { 10, 11, 12};
    m_state.player->m_walking[m_state.player->DOWN]   = new int[3] { 1, 2, 3};

    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->LEFT];  // start looking left
    m_state.player->m_animation_frames = 4;
    m_state.player->m_animation_index  = 0;
    m_state.player->m_animation_time   = 0.0f;
    m_state.player->m_animation_cols   = 3;
    m_state.player->m_animation_rows   = 4;
    m_state.player->set_height(0.8f);
    m_state.player->set_width(0.8f);
    
    // Jumping
    m_state.player->m_jumping_power = 7.0f;
    
    /**
     Enemies' stuff */
    m_state.enemies = new Entity[ENEMY_COUNT];
    //first
    m_state.enemies[0].set_entity_type(ENEMY);
    m_state.enemies[0].set_ai_type(GUARD);
    m_state.enemies[0].set_ai_state(IDLE);
    m_state.enemies[0].set_ai_state(JUMPING);
    m_state.enemies[0].m_texture_id = enemy_texture_id_1;
    m_state.enemies[0].set_position(glm::vec3(6.5f, 0.0f, 0.0f));
    m_state.enemies[0].set_movement(glm::vec3(0.0f));
    m_state.enemies[0].set_speed(1.0f);
    m_state.enemies[0].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    m_state.enemies[0].m_jumping_power = 0.2f;
    
    
    m_state.enemies[1].set_entity_type(ENEMY);
    m_state.enemies[1].set_ai_type(GUARD);
    m_state.enemies[1].set_ai_state(IDLE);
    m_state.enemies[1].m_texture_id = enemy_texture_id_2;
    m_state.enemies[1].set_position(glm::vec3(15.0f, 1.0f, 0.0f));
    m_state.enemies[1].set_movement(glm::vec3(0.0f));
    m_state.enemies[1].set_speed(1.0f);
    m_state.enemies[1].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    
    
    m_state.enemies[2].set_entity_type(ENEMY);
    m_state.enemies[2].set_ai_type(GUARD);
    m_state.enemies[2].set_ai_state(IDLE);
    m_state.enemies[2].m_texture_id = enemy_texture_id_3;
    m_state.enemies[2].set_position(glm::vec3(25.0f, 3.0f, 0.0f));
    m_state.enemies[2].set_movement(glm::vec3(0.0f));
    m_state.enemies[2].set_speed(1.0f);
    m_state.enemies[2].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    
    //projectiles
//    m_state.projectiles = new Entity[PROJECTILE_COUNT];
    
    
    /**44100,
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.bgm = Mix_LoadMUS("assets/simple_and_clean.mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(30.0f);
    
    m_state.jump_sfx = Mix_LoadWAV("assets/jumpland.wav");
}



void LevelA::update(float delta_time)
{
    m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
    
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_state.enemies[i].update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);

        if (m_state.player->check_collision(&m_state.enemies[i]))
        {
            if (fabs(m_state.enemies[i].get_position().y - m_state.player->get_position().y) < 0.2f)
            {
                // player collided vertically
                m_state.player->deactivate();
            }
            else if (fabs(m_state.enemies[i].get_position().x - m_state.player->get_position().x) < 0.1f && m_state.player->get_jumping())
            {
                // player collided horizontally while jumping
                m_state.player->deactivate();
            }
             if (fabs(m_state.player->get_position().y - m_state.enemies[i].get_position().y) < 0.2f && m_state.player->get_jumping())
            {
                // eemy collided vertically while player is jumping
                m_state.enemies[i].deactivate();
            }
            else if (fabs(m_state.player->get_position().x - m_state.enemies[i].get_position().x) < 0.2f && m_state.player->get_jumping())
            {
                // eemy collided horizontally while player is jumping
                m_state.enemies[i].deactivate();
            }
        }
        else if (!m_state.player->get_active())
        {
        
        }
    }
}

void LevelA::render(ShaderProgram *program)
{
    m_state.map->render(program);
    m_state.player->render(program);
    for(int i =0; i < ENEMY_COUNT; i++)  m_state.enemies[i].render(program);


    
}
