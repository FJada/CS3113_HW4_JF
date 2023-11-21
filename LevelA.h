#include "Scene.h"

class LevelA : public Scene {
public:
    
    int KILLED_COUNT = 0;
    int ENEMY_COUNT = 3;
    int PROJECTILE_COUNT = 15;
    
    ~LevelA();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
