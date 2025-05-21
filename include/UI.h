enum ScreenType
{
    MAIN, GAME, PAUSE
};

enum ButtonType {
    START, SETTINGS, QUIT, STANDARD
};

struct Image 
{
    SDL_Texture* texture;
    vec2 pos;
    SDL_FRect rect;

    mat3 model;
};

struct TextElement
{
    vec2 pos;
};

struct Button {
    TextElement text;
    ButtonType type;

    SDL_FRect rect;
    float color[4] = {255, 0, 0, 255};
    float highlight[4] = {255, 255, 255, 255};

    vec2 pos;
    int offsetNum;
    bool clicked;
};


class UI {
private:
    ScreenType currentScreen;
    float widthUI = 300, heightUI = 150;
    float offset = 10;
public:
    std::vector<Button> buttons;
    std::vector<Image> images;

    UI(ScreenType screen, int width, int height)
    {

        
        widthUI = width / 2;
        heightUI = height / 7;

        //Preset
        if (screen == MAIN)
        {
            Button start, settings, quit;

            // Main menu
            start.offsetNum = 4;
            start.type = START;
            start.rect = {(float)(width / 2) - (float)(widthUI / 2), (float)((height * start.offsetNum) / 7) - (float)(heightUI), widthUI, heightUI};
            buttons.push_back(start);

            settings.offsetNum = 6;
            settings.type = SETTINGS;
            settings.rect = {(float)(width / 2) - (float)(widthUI / 2), (float)((height * settings.offsetNum) / 7) - (float)(heightUI), widthUI, heightUI};
            buttons.push_back(settings);

            quit.offsetNum = 7;
            quit.type = QUIT;
            quit.rect = {(float)(width / 2) - (float)(widthUI / 2), (float)((height * quit.offsetNum) / 7) - (float)(heightUI), widthUI, heightUI};
            buttons.push_back(quit);
        }
        
    }

    void addButton(vec2 position, vec2 size){
        Button temp;

        temp.offsetNum = 1;
        temp.type = STANDARD;
        temp.rect = {position.x, position.y, position.y - size.y / 2, position.x - size.x / 2};
        buttons.push_back(temp);
    }

    void addImage(vec2 pos, vec2 size, std::string flieLoc, SDL_Renderer* renderer){
        const char *path = flieLoc.c_str();

        Image background;
        background.pos = pos;
        background.rect = {pos.x, pos.y, size.x, size.y};
        background.texture = IMG_LoadTexture(renderer, path);
        background.model[0][2] = pos.x;
        background.model[1][2] = pos.y;

        SDL_SetTextureScaleMode(background.texture, SDL_SCALEMODE_NEAREST); // Optimized for pixel art rendering

        images.push_back(background);
    }

    void addText(vec2 pos){
        
    }

    //Fix to aspect ratio instead
    void resize(int width, int height){
        widthUI = width / 3;
        heightUI = height / 7;
        for (auto &button : buttons)
        {
            std::cout << width << " " << height << "\n";
            button.rect = {(float)(width / 2) - (float)(widthUI / 2), (float)((height * button.offsetNum) / 7) - (float)(heightUI), widthUI, heightUI};
        }
    }

    void eventHandle(ButtonType bType)
    {

    }

    void startGame()
    {
        buttons.clear();
    }

    void draw(SDL_Renderer* renderer){

        for (auto& element : buttons)
        {
            SDL_SetRenderDrawColor(renderer, element.color[0], element.color[1], element.color[2], element.color[3] ); // Red
            SDL_RenderRect(renderer, &element.rect);
        }

        
    }

    void drawBackground(SDL_Renderer* renderer, mat3& viewproj, int width, int height)
    {
        
        for (auto &element : images)
        {
            mat3 modelViewProj = element.model * viewproj;

            float tX = (modelViewProj[0][2] / 2) + (width / 2);
            float tY = -(modelViewProj[1][2] / 2) + (height / 2);

            element.rect.x = tX;
            element.rect.y = tY;

            SDL_RenderTexture(renderer, element.texture, NULL, &element.rect);
        }
    }
};
