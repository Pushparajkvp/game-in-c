#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include<stdio.h>
#include<time.h>
int r,q;
const float grav=0.3;

typedef struct
{
    int count,bools,doubles,life,dead;
    float y,x,ix,iy,dy,dx;
}dog;

typedef struct
{
    int life,dead,shoot;
    float x,y,ix,iy;
}target;
typedef struct
{
    int dead;
    float x,y,ix,iy;
}bomb;
typedef struct
{
    int count,bools,doubles,life,dead;
    float y,x,ix,iy,dy,dx;
}enemy;
typedef struct
{
    int count,bools,doubles,life;
    float x,y,ix,iy;
}brick;

typedef struct
{
    float ix,iy,x,y;
    int dir,blast,dead;
}bullets;
typedef struct
{
    float ix,iy,x,y;
    int dir,blast,dead;
}ebullet;
typedef struct
{
    float ix,iy,x,y;
}dahealth;
typedef struct
{
    float ix,iy,x,y;
}enemyhealth;
typedef struct
{
    target target[100];
    int bullno;
    bomb bomb[100];
    int gametime;
    int counts;
    int ecounts;
    float screen;
    dahealth dahealth;
    enemyhealth enemyhealth;
    bullets bullets[100];
    ebullet ebullet[100];
    brick brick[101];
    dog dog;
    enemy enemy;
    SDL_Texture *texture[8];
    SDL_Texture *etexture[8];
    SDL_Texture *bricks;
    SDL_Texture *sky;
    SDL_Texture *bullet;
    SDL_Texture *ebullets;
    SDL_Texture *blast;
    SDL_Texture *dahp;
    SDL_Texture *daname;
    SDL_Texture *enemyname;
    SDL_Texture *re;
    SDL_Texture *bombs;
    SDL_Texture *targets;
    int time;
    int etime;

}game;

int collidebull(game *game,int j)
{
    int i;
    float bx=game->bullets[j].x,by=game->bullets[j].y,bw=game->bullets[j].ix/2,bh=game->bullets[j].iy/2;
    for(i=0;i<101;i++)
    {
        bw=game->bullets[j].ix/2;
        bh=game->bullets[j].iy/2;
        if(bx>0 && by>0)
        {
        float brix=game->brick[i].x+game->screen,briy=game->brick[i].y,briw=game->brick[i].ix,brih=game->brick[i].iy-20;

        if(bx+bw>brix && bx<brix && by+bh>briy && by<brih+briy)
            return 1;
        if(bx<brix+briw && bx+bw>brix+briw && by+bh>briy && by<brih+briy)
            return 1;
        if(by+bh>briy && by<briy && bx+bw>brix && bx<brix+briw)
            return 1;
        if(by<briy+brih && by+bh>brih+briy && bx+bw>brix && bx<brix+briw)
            return 1;

        brix=game->target[i].x;
        briy=game->target[i].y;
        briw=game->target[i].ix/2;
        brih=game->target[i].iy;
          bw=game->bullets[i].ix/5;
          bh=game->bullets[i].iy/2;
          if(brix>0 && briy>0)
          {
           if(bx+bw>brix && bx<brix && by+bh>briy && by<brih+briy)
           {
               game->target[i].life -=1;
               return 3;
           }
          if(bx<brix+briw && bx+bw>brix+briw && by+bh>briy && by<brih+briy)
           {
               game->target[i].life -=1;
               return 3;
           }
          if(by+bh>briy && by<briy && bx+bw>brix && bx<brix+briw)
           {
               game->target[i].life -=1;
               return 3;
           }
          if(by<briy+brih && by+bh>brih+briy && bx+bw>brix && bx<brix+briw)
           {
               game->target[i].life -=1;
               return 3;
           }
          }
          }

    }

    for(i=0;i<100;i++)
    {
        if(bx>0 && by>0)
        {
        bw=game->bullets[j].ix/5;
        float brix=game->ebullet[i].x,briy=game->ebullet[i].y,briw=game->ebullet[i].ix/5,brih=game->ebullet[i].iy;
          if(brix>0 && briy>0)
          {
           if(bx+bw>brix && bx<brix && by+bh>briy && by<brih+briy)
            return 1;
          if(bx<brix+briw && bx+bw>brix+briw && by+bh>briy && by<brih+briy)
            return 1;
          if(by+bh>briy && by<briy && bx+bw>brix && bx<brix+briw)
            return 1;
          if(by<briy+brih && by+bh>brih+briy && bx+bw>brix && bx<brix+briw)
            return 1;
          }
        }

    }
          float brix=game->enemy.x+game->screen,briy=game->enemy.y,briw=game->enemy.ix/5,brih=game->enemy.iy;
          bw=game->bullets[i].ix/5;
          bh=game->bullets[i].iy/5;
          if(brix>0 && briy>0)
          {
           if(bx+bw>brix && bx<brix && by+bh>briy && by<brih+briy)
            return 2;
          if(bx<brix+briw && bx+bw>brix+briw && by+bh>briy && by<brih+briy)
            return 2;
          if(by+bh>briy && by<briy && bx+bw>brix && bx<brix+briw)
            return 2;
          if(by<briy+brih && by+bh>brih+briy && bx+bw>brix && bx<brix+briw)
            return 2;
          }

    for(i=0;i<100;i++)
    {
        if(bx>0 && by>0)
        {
        bw=game->bullets[j].ix/5;
        bh=game->bullets[j].iy/2;
        float brix=game->bomb[i].x+game->screen,briy=game->bomb[i].y,briw=game->bomb[i].ix,brih=game->bomb[i].iy;
          if(brix>0 && briy>0)
          {
           if(bx+bw>brix && bx<brix && by+bh>briy && by<brih+briy)
           {
               game->bomb[i].dead=1;
               game->bomb[i].x=0;
               game->bomb[i].y=0;
               return 4;
           }
          if(bx<brix+briw && bx+bw>brix+briw && by+bh>briy && by<brih+briy)
           {
               game->bomb[i].dead=1;
               game->bomb[i].x=0;
               game->bomb[i].y=0;
               return 4;
           }
          if(by+bh>briy && by<briy && bx+bw>brix && bx<brix+briw)
           {
               game->bomb[i].dead=1;
               game->bomb[i].x=0;
               game->bomb[i].y=0;
               return 4;
           }
          if(by<briy+brih && by+bh>brih+briy && bx+bw>brix && bx<brix+briw)
           {
               game->bomb[i].dead=1;
               game->bomb[i].x=0;
               game->bomb[i].y=0;
               return 4;
           }
          }
        }

    }


          return 0;
}
int ebcollide(game *game,int j)
{
    int i;
    float bx=game->ebullet[j].x,by=game->ebullet[j].y,bw=game->ebullet[j].ix/2,bh=game->ebullet[j].iy/2;
    for(i=0;i<101;i++)
    {
        bw=game->ebullet[j].ix/2;
        bh=game->ebullet[j].iy/2;
        if(bx>0 && by>0)
        {
        float brix=game->brick[i].x+game->screen,briy=game->brick[i].y,briw=game->brick[i].ix,brih=game->brick[i].iy-20;

        if(bx+bw>brix && bx<brix && by+bh>briy && by<brih+briy)
            return 1;
        if(bx<brix+briw && bx+bw>brix+briw && by+bh>briy && by<brih+briy)
            return 1;
        if(by+bh>briy && by<briy && bx+bw>brix && bx<brix+briw)
            return 1;
        if(by<briy+brih && by+bh>brih+briy && bx+bw>brix && bx<brix+briw)
            return 1;

        brix=game->target[i].x;
        briy=game->target[i].y;
        briw=game->target[i].ix/2;
        brih=game->target[i].iy;
          bw=game->ebullet[i].ix/5;
          bh=game->ebullet[i].iy/2;
          if(brix>0 && briy>0)
          {
           if(bx+bw>brix && bx<brix && by+bh>briy && by<brih+briy)
           {
               game->target[i].life -=1;
                return 3;
           }
           if(bx<brix+briw && bx+bw>brix+briw && by+bh>briy && by<brih+briy)
           {
               game->target[i].life -=1;
                return 3;
           }
           if(by+bh>briy && by<briy && bx+bw>brix && bx<brix+briw)
           {
               game->target[i].life -=1;
                return 3;
           }
           if(by<briy+brih && by+bh>brih+briy && bx+bw>brix && bx<brix+briw)
            {
               game->target[i].life -=1;
                return 3;
           }
          }
        }

    }

    for(i=0;i<100;i++)
    {
        if(bx>0 && by>0)
        {
         bw=game->ebullet[j].ix/6;
         bh=game->ebullet[j].iy/2;
         float brix=game->bullets[i].x,briy=game->bullets[i].y,briw=game->bullets[i].ix/6,brih=game->bullets[i].iy;
         if(brix>0 && briy>0)
         {
          if(bx+bw>brix && bx<brix && by+bh>briy && by<brih+briy)
            return 1;
          if(bx<brix+briw && bx+bw>brix+briw && by+bh>briy && by<brih+briy)
            return 1;
          if(by+bh>briy && by<briy && bx+bw>brix && bx<brix+briw)
            return 1;
          if(by<briy+brih && by+bh>brih+briy && bx+bw>brix && bx<brix+briw)
            return 1;
         }

        }

    }
          float brix=game->dog.x+game->screen,briy=game->dog.y,briw=game->dog.ix/5,brih=game->dog.iy;
          bw=game->bullets[i].ix/5;
          bh=game->bullets[i].iy/5;
          if(brix>0 && briy>0)
          {
           if(bx+bw>brix && bx<brix && by+bh>briy && by<brih+briy)
            return 2;
          if(bx<brix+briw && bx+bw>brix+briw && by+bh>briy && by<brih+briy)
            return 2;
          if(by+bh>briy && by<briy && bx+bw>brix && bx<brix+briw)
            return 2;
          if(by<briy+brih && by+bh>brih+briy && bx+bw>brix && bx<brix+briw)
            return 2;
          }

    for(i=0;i<100;i++)
    {
        if(bx>0 && by>0)
        {
         bw=game->ebullet[j].ix/6;
         bh=game->ebullet[j].iy/2;
         float brix=game->bomb[i].x+game->screen,briy=game->bomb[i].y,briw=game->bomb[i].ix,brih=game->bomb[i].iy;
         if(brix>0 && briy>0)
         {
          if(bx+bw>brix && bx<brix && by+bh>briy && by<brih+briy)
           {
               game->bomb[i].dead=1;
               game->bomb[i].x=0;
               game->bomb[i].y=0;
               return 4;
           }
          if(bx<brix+briw && bx+bw>brix+briw && by+bh>briy && by<brih+briy)
           {
               game->bomb[i].dead=1;
               game->bomb[i].x=0;
               game->bomb[i].y=0;
               return 4;
           }
          if(by+bh>briy && by<briy && bx+bw>brix && bx<brix+briw)
           {
               game->bomb[i].dead=1;
               game->bomb[i].x=0;
               game->bomb[i].y=0;
               return 4;
           }
          if(by<briy+brih && by+bh>brih+briy && bx+bw>brix && bx<brix+briw)
           {
               game->bomb[i].dead=1;
               game->bomb[i].x=0;
               game->bomb[i].y=0;
               return 4;
           }
         }

        }

    }

    return 0;



}
void collide(game *game)
{
  int i;
   float dh = game->dog.iy ,dw = game->dog.ix  , dx = game->dog.x , dy = game->dog.y;
  for(i=0;i<101;i++)
  {
      float brih = game->brick[i].iy , briw = game->brick[i].ix , brix = game->brick[i].x , briy = game->brick[i].y;

        if(dy+dh/2>briy && dy<briy+brih)
        {
           //left edge
          if(dx+dw>brix && dx < brix && game->dog.dx>0)
          {
               game->dog.x = brix-dw;
               dx=brix-dw;
               //printf("left\n");
          }
          //right edge
          else if(dx<brix+briw && dx+dw>brix+briw && game->dog.dx<0)
          {
              game->dog.x = brix+briw;
              dx=brix+briw;
          }
        }
        if(dx+dw>brix && dx<brix+briw)
        {
          //up edge
          if(dy+dh>briy && dy < briy && game->dog.dy>0)
          {
              game->dog.y = briy-dh;
              game->dog.dy = 0;
              game->dog.bools = 1;
              game->dog.doubles=0;
          }
          //down
          else if(dy<briy+brih && dy>briy && game->dog.dy < 0)
          {
              game->dog.y = briy+brih;
              game->dog.dy = 0;
          }

        }
  }
}
void ecollide(game *game)
{
   int i;
  for(i=0;i<101;i++)
  {
      float dh = game->enemy.iy ,dw = game->enemy.ix  , dx = game->enemy.x , dy = game->enemy.y;
      float brih = game->brick[i].iy , briw = game->brick[i].ix , brix = game->brick[i].x , briy = game->brick[i].y;

        if(dy+dh/2>briy && dy<briy+brih)
        {
           //left edge
          if(dx+dw>brix && dx < brix && game->enemy.dx>0)
          {
               game->enemy.x = brix-dw;
               dx=brix-dw;
               //printf("left\n");
          }
          //right edge
          else if(dx<brix+briw && dx+dw>brix+briw && game->enemy.dx<0)
          {
              game->enemy.x = brix+briw;
              dx=brix+briw;
           //   printf("right\n");
          }
        }
        if(dx+dw>brix && dx<brix+briw)
        {
          //up edge
          if(dy+dh>briy && dy < briy && game->enemy.dy>0)
          {
              game->enemy.y = briy-dh;
              game->enemy.dy = 0;
              game->enemy.bools = 1;
              game->enemy.doubles=0;
            //  printf("up\n");
          }
          //down
          else if(dy<briy+brih && dy>briy && game->enemy.dy < 0)
          {
              game->enemy.y = briy+brih;
              game->enemy.dy = 0;
             // printf("down\n");
          }

        }
  }
}
void ballscollide(game *game)
{
    int i;
    float bx=game->dog.x+game->screen,by=game->dog.y,bw=game->dog.ix,bh=game->dog.iy;
    for(i=0;i<100;i++)
    {
     float brix=game->target[i].x,briy=game->target[i].y,briw=game->target[i].ix,brih=game->target[i].iy;

        if(bx+bw>brix && bx<brix && by+bh>briy && by<brih+briy && game->dog.dx>0)
            game->dog.dx=0;
        if(bx<brix+briw && bx+bw>brix+briw && by+bh>briy && by<brih+briy && game->dog.dx<0)
            game->dog.dx=0;
        if(by+bh>briy && by<briy && bx+bw>brix && bx<brix+briw && game->dog.dy>0)
            game->dog.dy=0;
        if(by<briy+brih && by+bh>brih+briy && bx+bw>brix && bx<brix+briw && game->dog.dy<0)
            game->dog.dy=0;
    }
    bx=game->enemy.x+game->screen;
    by=game->enemy.y;
    bw=game->enemy.ix;
    bh=game->enemy.iy;
    for(i=0;i<100;i++)
    {
     float brix=game->target[i].x,briy=game->target[i].y,briw=game->target[i].ix,brih=game->target[i].iy;

        if(bx+bw>brix && bx<brix && by+bh>briy && by<brih+briy && game->enemy.dx>0)
            game->enemy.dx=0;
        if(bx<brix+briw && bx+bw>brix+briw && by+bh>briy && by<brih+briy && game->enemy.dx<0)
            game->enemy.dx=0;
        if(by+bh>briy && by<briy && bx+bw>brix && bx<brix+briw && game->enemy.dy>0)
            game->enemy.dy=0;
        if(by<briy+brih && by+bh>brih+briy && bx+bw>brix && bx<brix+briw && game->enemy.dy<0)
            game->enemy.dy=0;
    }

}

void render(SDL_Renderer *renderer,game *game)
{
    SDL_Surface *surface;

    surface = IMG_Load("bomb.png");
    if(surface == NULL )
        printf("%s",SDL_GetError());
    game->bombs = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("target.png");
    if(surface == NULL )
        printf("%s",SDL_GetError());
    game->targets = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("dahp.png");
    if(surface == NULL )
        printf("%s",SDL_GetError());
    game->dahp = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("re.png");
    if(surface == NULL )
        printf("%s",SDL_GetError());
    game->re = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("daname.png");
    if(surface == NULL )
        printf("%s",SDL_GetError());
    game->daname = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);


    surface = IMG_Load("enemyname.png");
    if(surface == NULL )
        printf("%s",SDL_GetError());
    game->enemyname = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);


    surface = IMG_Load("dastand.png");
    if(surface == NULL )
        printf("%s",SDL_GetError());
    game->texture[0] = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("enemystand.png");
    if(surface == NULL )
        printf("%s",SDL_GetError());
    game->etexture[0] = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("dawalk1.png");
    if(surface == NULL )
        printf("%s",SDL_GetError());
    game->texture[1] = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);


    surface = IMG_Load("enemywalk1.png");
    if(surface == NULL )
        printf("%s",SDL_GetError());
    game->etexture[1] = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("dawalk2.png");
    if(surface == NULL )
        printf("%s",SDL_GetError());
    game->texture[2] = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("enemywalk2.png");
    if(surface == NULL )
        printf("%s",SDL_GetError());
    game->etexture[2] = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("dawalk1left.png");
    if(surface == NULL )
        printf("%s",SDL_GetError());
    game->texture[3] = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("enemywalk1left.png");
    if(surface == NULL )
        printf("%s",SDL_GetError());
    game->etexture[3] = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("dawalk2left.png");
    if(surface == NULL )
    printf("%s",SDL_GetError());
    game->texture[4]=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("enemywalk2left.png");
    if(surface == NULL )
    printf("%s",SDL_GetError());
    game->etexture[4]=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);


    surface = IMG_Load("bricks.png");
    if(surface == NULL )
        printf("%s",SDL_GetError());
    game->bricks = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("sky.png");
    if(surface == NULL)
        printf("%s",SDL_GetError());
    game->sky = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

     surface = IMG_Load("bullet.png");
    if(surface == NULL)
        printf("%s",SDL_GetError());
    game->bullet = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("ebullet.png");
    if(surface == NULL)
        printf("%s",SDL_GetError());
    game->ebullets = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

     surface = IMG_Load("dastand1.png");
    if(surface == NULL)
        printf("%s",SDL_GetError());
    game->texture[5] = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

     surface = IMG_Load("enemystand1.png");
    if(surface == NULL)
        printf("%s",SDL_GetError());
    game->etexture[5] = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

     surface = IMG_Load("blast.png");
    if(surface == NULL)
        printf("%s",SDL_GetError());
    game->blast = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("dadead.png");
    if(surface == NULL)
        printf("%s",SDL_GetError());
    game->texture[6] = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("enemydead.png");
    if(surface == NULL)
        printf("%s",SDL_GetError());
    game->etexture[6] = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
}
int events(SDL_Renderer *renderer,game *game)
{
    int done=1,dash;
    SDL_Event events;
    while(SDL_PollEvent(&events))
    {
        switch(events.type)
        {
        case SDL_WINDOWEVENT_CLOSE :SDL_Quit();
                                    done=0;
                                    break;
        case SDL_QUIT : done=0;
                        break;
        }

    }

       const Uint8 *states = SDL_GetKeyboardState(NULL);
        if(states[SDL_SCANCODE_ESCAPE])
        {
            SDL_Quit();
            done=0;
        }
        if(game->dog.life <=0 && game->enemy.life <=0)
        {
           if(states[SDL_SCANCODE_TAB])
           {
               int i;
               game->dog.life = 600;
               game->enemy.life =600;
               r=0;
               q=0;
               game->dog.x = 100;
               game->enemy.x = 150;
               game->dog.y = 450;
               game->enemy.y = 450;
               game->screen=0;
               for(i=0;i<100;i++)
               {
                    game->target[i].life=200;
                    game->target[i].dead =1;
               }
               game->enemy.dead=0;
               game->dog.dead=0;


           }
        }
    if(game->dog.life > 0)
    {
        if(states[SDL_SCANCODE_D])
        {
             if((game->dog.count)%50>=0 && (game->dog.count)%50<=24)
            {
            r=1;
            game->dog.dx += 0.8;
            if(game->dog.dx > 6)
                game->dog.dx = 6;
            }
            if((game->dog.count)%50>24 && (game->dog.count)%50<=49)
            {
            r=2;
            game->dog.dx += 0.8;
            if(game->dog.dx > 6)
                game->dog.dx = 6;
            }
            if(game->dog.dx < 6)
            game->dog.count+=1;
            else
            game->dog.count+=2;

        }
        else if(states[SDL_SCANCODE_A])
        {
             if((game->dog.count)%50>=0 && (game->dog.count)%50<=24)
            {
            r=3;
            game->dog.dx -= 0.8;
            if(game->dog.dx < -6)
                game->dog.dx = -6;
            }
            if((game->dog.count)%50>24 && (game->dog.count)%50<=49)
            {
            r=4;
            game->dog.dx -= 0.8;
            if(game->dog.dx < -6)
                game->dog.dx = -6;
            }
            if(game->dog.dx < -6)
            game->dog.count+=1;
            else
            game->dog.count+=2;
        }
        else
        {
          game->dog.dx *= 0.8;
          if(fabs(game->dog.dx) < 0.1)
            game->dog.dx = 0;
          if(r==1 || r==2)
             r=0;
          if(r==3 || r==4)
             r=5;

        }
        if(states[SDL_SCANCODE_W])
        {
            if(game->dog.bools == 1)
            {
            game->dog.dy = -10;
            game->dog.bools = 0;
            }
            if(game->dog.doubles==10)
            game->dog.dy = -10;
            game->dog.doubles+=1;
        }
        if(states[SDL_SCANCODE_A] && states[SDL_SCANCODE_D])
        {
           game->dog.dx=0;
           r=0;
        }
        if(states[SDL_SCANCODE_F])
        {
         if(game->time > 10 )
         {
         dash = game->counts;
         game->bullets[dash].x = game->dog.x+game->screen;
         game->bullets[dash].y = game->dog.y;
          if(r==3 || r==4 || r== 5)
            game->bullets[dash].dir=0;
          else
         game->bullets[dash].dir=1;
         game->counts += 1;
         if(dash > 90)
           game->counts = 0;
         game->time = 0;
         }
        }

    }


   if(game->enemy.life >0)
   {
    if(states[SDL_SCANCODE_RIGHT])
        {
             if((game->enemy.count)%50>=0 && (game->enemy.count)%50<=24)
            {
            q=1;
            game->enemy.dx += 0.8;
            if(game->enemy.dx > 6)
                game->enemy.dx = 6;
            }
            if((game->enemy.count)%50>24 && (game->enemy.count)%50<=49)
            {
            q=2;
            game->enemy.dx += 0.8;
            if(game->enemy.dx > 6)
                game->enemy.dx = 6;
            }
            if(game->enemy.dx < 6)
            game->enemy.count+=1;
            else
            game->enemy.count+=2;

        }
        else if(states[SDL_SCANCODE_LEFT])
        {
             if((game->enemy.count)%50>=0 && (game->enemy.count)%50<=24)
            {
            q=3;
            game->enemy.dx -= 0.8;
            if(game->enemy.dx < -6)
                game->enemy.dx = -6;
            }
            if((game->enemy.count)%50>24 && (game->enemy.count)%50<=49)
            {
            q=4;
            game->enemy.dx -= 0.8;
            if(game->enemy.dx < -6)
                game->enemy.dx = -6;
            }
            if(game->enemy.dx < -6)
            game->enemy.count+=1;
            else
            game->enemy.count+=2;
        }
        else
        {
          game->enemy.dx *= 0.8;
          if(fabs(game->enemy.dx) < 0.1)
            game->enemy.dx = 0;
          if(q==1 || q==2)
             q=0;
          if(q==3 || q==4)
             q=5;
        }

        if(states[SDL_SCANCODE_UP])
        {
            if(game->enemy.bools == 1)
            {
            game->enemy.dy = -10;
            game->enemy.bools = 0;
            }
            if(game->enemy.doubles==10)
            game->enemy.dy = -10;
            game->enemy.doubles+=1;
        }
        if(states[SDL_SCANCODE_LEFT] && states[SDL_SCANCODE_RIGHT])
        {
           game->enemy.dx=0;
           q=0;
        }
        if(states[SDL_SCANCODE_SPACE])
        {
         if(game->etime > 10 )
         {
         dash = game->ecounts;
         game->ebullet[dash].x = game->enemy.x+game->screen;
         game->ebullet[dash].y = game->enemy.y;
          if(q==3 || q==4 || q== 5)
            game->ebullet[dash].dir=0;
          else
         game->ebullet[dash].dir=1;
         game->ecounts += 1;
         if(dash > 90)
           game->ecounts = 0;
         game->etime = 0;
         }
        }
   }


return done;
}

void print(SDL_Renderer *renderer,game *game,int i,int q)
{

    SDL_SetRenderDrawColor(renderer,153,204,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_Rect rectangle = {100,100,550,290};
    SDL_RenderCopy(renderer, game->sky, NULL, &rectangle);
    SDL_Rect rect = {game->dog.x+game->screen,game->dog.y,game->dog.ix,game->dog.iy};
    SDL_RenderCopy(renderer,game->texture[i],NULL,&rect);
    for(i=0;i<100;i++)
    {
    if(i==2)
        continue;
    if(i%4==0 && i>4)
    {
    SDL_Rect rect = {(game->screen)+(game->brick[i].x),game->brick[i].y=450,game->brick[i].ix,game->brick[i].iy};
    SDL_RenderCopy(renderer,game->bricks,NULL,&rect);
     if(game->target[i].dead > 0)
     {
     SDL_Rect rects = {game->target[i].x=(game->brick[i].x)+(game->brick[i].ix)+(game->screen)-(game->dog.ix)-20,game->target[i].y=(game->brick[i].y)-(game->dog.iy),game->target[i].ix=game->dog.ix+20,game->target[i].iy=game->dog.iy};
     SDL_RenderCopyEx(renderer,game->targets,NULL,&rects,0,NULL,1);
     }

    continue;
    }
    if(i%6==0 && i>4)
    {
    SDL_Rect rect = {(game->screen)+(game->brick[i].x),game->brick[i].y=350,game->brick[i].ix,game->brick[i].iy};
    SDL_RenderCopy(renderer,game->bricks,NULL,&rect);
    if(game->target[i].dead > 0)
     {
     SDL_Rect rects = {game->target[i].x=(game->brick[i].x)+(game->brick[i].ix)+(game->screen)-(game->dog.ix)-20,game->target[i].y=(game->brick[i].y)-(game->dog.iy),game->target[i].ix=game->dog.ix+20,game->target[i].iy=game->dog.iy};
     SDL_RenderCopyEx(renderer,game->targets,NULL,&rects,0,NULL,1);
     }
    continue;
    }
    if(i==5)
    {
     SDL_Rect rect = {(game->screen)+(game->brick[i].x),game->brick[i].y=450,game->brick[i].ix,game->brick[i].iy};
     SDL_RenderCopy(renderer,game->bricks,NULL,&rect);
     if(game->target[i].dead > 0)
     {
     SDL_Rect rects = {game->target[i].x=(game->brick[i].x)+(game->brick[i].ix)+(game->screen)-(game->dog.ix)-20,game->target[i].y=(game->brick[i].y)-(game->dog.iy),game->target[i].ix=game->dog.ix+20,game->target[i].iy=game->dog.iy};
     SDL_RenderCopyEx(renderer,game->targets,NULL,&rects,0,NULL,1);
     }
     continue;
    }
    SDL_Rect rect = {(game->screen)+(game->brick[i].x),game->brick[i].y,game->brick[i].ix,game->brick[i].iy};
    SDL_RenderCopy(renderer,game->bricks,NULL,&rect);
    if(game->target[i].dead > 0)
     {
     SDL_Rect rects = {game->target[i].x=(game->brick[i].x)+(game->brick[i].ix)+(game->screen)-(game->dog.ix)-20,game->target[i].y=(game->brick[i].y)-(game->dog.iy),game->target[i].ix=game->dog.ix+20,game->target[i].iy=game->dog.iy};
     SDL_RenderCopyEx(renderer,game->targets,NULL,&rects,0,NULL,1);
     }
    }
    SDL_Rect rects = {(game->brick[100].x=600)+game->screen,game->brick[100].y=450,game->brick[100].ix,game->brick[100].iy};
    SDL_RenderCopy(renderer,game->bricks,NULL,&rects);

    for(i=0;i<100;i++)
     {
      if(game->bullets[i].dead>0)
      {
        if(game->bullets[i].x >0 && game->bullets[i].y>0 && game->bullets[i].dead==2)
        {
         SDL_Rect recto = {game->bullets[i].x,game->bullets[i].y,game->bullets[i].ix,game->bullets[i].iy};
         SDL_RenderCopy(renderer,game->bullet,NULL,&recto);
        }
        if(game->bullets[i].dead == 1)
        {
         SDL_Rect recto = {game->bullets[i].x,game->bullets[i].y,game->bullets[i].ix,game->bullets[i].iy};
         SDL_RenderCopy(renderer,game->blast,NULL,&recto);
        }
      }

     }


    SDL_Rect rectx = {game->enemy.x+game->screen,game->enemy.y,game->enemy.ix,game->enemy.iy};
    SDL_RenderCopy(renderer,game->etexture[q],NULL,&rectx);

    for(i=0;i<100;i++)
     {
      if(game->ebullet[i].dead>0)
      {
        if(game->ebullet[i].x >0 && game->ebullet[i].y>0 && game->ebullet[i].dead==2)
        {
         SDL_Rect recto = {game->ebullet[i].x,game->ebullet[i].y,game->ebullet[i].ix,game->ebullet[i].iy};
         SDL_RenderCopy(renderer,game->ebullets,NULL,&recto);
        }
        if(game->ebullet[i].dead == 1)
        {
         SDL_Rect recto = {game->ebullet[i].x,game->ebullet[i].y,game->ebullet[i].ix,game->ebullet[i].iy};
         SDL_RenderCopy(renderer,game->blast,NULL,&recto);
        }
       if(game->bomb[i].dead == 0)
       {
         SDL_Rect recto = {game->bomb[i].x+game->screen,game->bomb[i].y,game->bomb[i].ix,game->bomb[i].iy};
         SDL_RenderCopy(renderer,game->bombs,NULL,&recto);
       }
      }

     }
    SDL_Rect recto = {game->dahealth.x,game->dahealth.y,(game->dahealth.ix)*(game->dog.life)/10,game->dahealth.iy};
    SDL_RenderCopy(renderer,game->dahp,NULL,&recto);

    SDL_Rect rectr = {game->enemyhealth.x,game->enemyhealth.y,(game->enemyhealth.ix)*(game->enemy.life)/10,game->enemyhealth.iy};
    SDL_RenderCopy(renderer,game->dahp,NULL,&rectr);

    SDL_Rect recttt = {50,10,50,70};
    SDL_RenderCopy(renderer,game->texture[0],NULL,&recttt);

    SDL_Rect recttts = {650,10,50,70};
    SDL_RenderCopy(renderer,game->etexture[0],NULL,&recttts);

    if(game->dog.life <=0 && game->enemy.life<=0)
    {
     SDL_SetRenderDrawColor(renderer,255,255,255,255);
     SDL_RenderClear(renderer);

     SDL_Rect recttts = {250,250,500,70};
     SDL_RenderCopy(renderer,game->re,NULL,&recttts);

    }
    game->target[0].x = -2;
    game->target[0].y = -2;
    game->target[0].dead = 0;
    game->target[1].x = -2;
    game->target[1].y = -2;
    game->target[1].dead = 0;

    SDL_RenderPresent(renderer);
}
void addbullet(game *game,int i)
{
    game->bomb[game->bullno].x=game->target[i].x-20-game->screen;
    game->bomb[game->bullno].y=game->target[i].y+20;
    game->bomb[game->bullno].dead = 0;
    game->bullno +=1;
    if(game->bullno>90)
        game->bullno=0;
}
void enemybull(game *game)
{
    int i;
    float brix=game->dog.x+game->screen,briy=game->dog.y,briw=game->dog.ix/5,brih=game->dog.iy;
    for(i=0;i<100;i++)
    {
        if(game->bomb[i].dead == 0)
        {
            
            float bx=game->bomb[i].x+game->screen,by=game->bomb[i].y,bw=game->bomb[i].ix/2,bh=game->bomb[i].iy/2;
            if(bx+bw>brix && bx<brix && by+bh>briy && by<brih+briy)
            {
                game->dog.life -= 100;
                game->bomb[i].dead=1;
                game->bomb[i].x =0;
                game->bomb[i].y=0;
                return;
            }
            if(bx<brix+briw && bx+bw>brix+briw && by+bh>briy && by<brih+briy)
            {
                game->dog.life -= 100;
                game->bomb[i].dead=1;
                game->bomb[i].x =0;
                game->bomb[i].y=0;
                return;
            }
            if(by+bh>briy && by<briy && bx+bw>brix && bx<brix+briw)
            {
                game->dog.life -= 100;
                game->bomb[i].dead=1;
                game->bomb[i].x =0;
                game->bomb[i].y=0;
                return;
            }
            if(by<briy+brih && by+bh>brih+briy && bx+bw>brix && bx<brix+briw)
            {
                game->dog.life -= 100;
                game->bomb[i].dead=1;
                game->bomb[i].x =0;
                game->bomb[i].y=0;
                return;
            }
        }
        
    }
    
    brix=game->enemy.x+game->screen;
    briy=game->enemy.y;
    briw=game->dog.ix/5;
    brih=game->enemy.iy;
    
    for(i=0;i<100;i++)
    {
        if(game->bomb[i].dead == 0)
        {
            float bx=game->bomb[i].x+game->screen,by=game->bomb[i].y,bw=game->bomb[i].ix/2,bh=game->bomb[i].iy/2;
            if(bx+bw>brix && bx<brix && by+bh>briy && by<brih+briy)
            {
                game->enemy.life -= 100;
                game->bomb[i].dead=1;
                game->bomb[i].x =0;
                game->bomb[i].y=0;
                return;
            }
            if(bx<brix+briw && bx+bw>brix+briw && by+bh>briy && by<brih+briy)
            {
                game->enemy.life -= 100;
                game->bomb[i].dead=1;
                game->bomb[i].x =0;
                game->bomb[i].y=0;
                return;
            }
            if(by+bh>briy && by<briy && bx+bw>brix && bx<brix+briw)
            {
                game->enemy.life -= 100;
                game->bomb[i].dead=1;
                game->bomb[i].x =0;
                game->bomb[i].y=0;
                return;
            }
            if(by<briy+brih && by+bh>brih+briy && bx+bw>brix && bx<brix+briw)
            {
                game->enemy.life -= 100;
                game->bomb[i].dead=1;
                game->bomb[i].x =0;
                game->bomb[i].y=0;
                return;
            }
        }
        
    }
}


void process(game *game)
{
  int i;
    enemybull(game);
    for(i=0;i<100;i++)
   {
      if(game->bullets[i].x >0 && game->bullets[i].y>0 && game->bullets[i].dead==2)
      {
       if(game->bullets[i].dir == 0)
        game->bullets[i].x-= 10;
       else
        game->bullets[i].x+= 10;

      }
      if(game->target[i].life <= 0)
      {
       game->target[i].dead=-1;
       game->target[i].x=0;
       game->target[i].y=0;
       game->target[i].ix=0;
       game->target[i].iy=0;
      }
   }

      if(game->dog.x>(-(game->screen)+800) && game->dog.dx>0 && game->enemy.x>(-(game->screen)))
      game->screen -=6;
      else if(game->enemy.x<=(-(game->screen)) && game->dog.x>(-(game->screen)+1000) && (r==1 || r==2))
      game->dog.dx=0;
      if(game->enemy.x>(-(game->screen)+800) && game->enemy.dx>0 && game->dog.x>(-(game->screen)) )
      game->screen -=6;
      else if(game->dog.x<=(-(game->screen)) && game->enemy.x>(-(game->screen)+1000) && (q==1 || q==2))
      game->enemy.dx=0;
      if(game->enemy.x<(-(game->screen)+400) && game->enemy.dx<0 && game->dog.x<(-(game->screen)+1150))
      game->screen +=6;
      else if(game->dog.x>=(-(game->screen)+1150)  && game->enemy.x<(-(game->screen)+200) && (q==3 || q==4))
      game->enemy.dx=0;
      if(game->dog.x<(-(game->screen)+400) && game->dog.dx<0 && game->enemy.x<(-(game->screen)+1150))
      game->screen +=6;
      else if(game->enemy.x>=(-(game->screen)+1150)  && game->dog.x<(-(game->screen)+200) && (r==3 || r==4))
      game->dog.dx=0;

      if((game->screen>0+game->dog.x-400 && game->dog.dx<0) || (game->screen >0+game->enemy.x-400 && game->enemy.dx<0))
      {

          if(game->screen >0+game->enemy.x && game->enemy.dx<0)
            game->enemy.dx=0;
          if(game->screen>0+game->dog.x && game->dog.dx<0)
            game->dog.dx=0;
          game->screen=0;
      }
  ballscollide(game);

  game->dog.x += game->dog.dx;
  game->dog.y += game->dog.dy;
  game->dog.dy += grav;
  game->time += 1;


  for(i=0;i<100;i++)
  {

      if(collidebull(game,i)==4 || collidebull(game,i)==2 || collidebull(game,i)==3 || collidebull(game,i)==1)
      {
       game->bullets[i].dead = 1;
       game->bullets[i].blast -= 1;
      }
      if(game->bullets[i].blast < 0)
        game->bullets[i].blast -= 1;
      if(game->bullets[i].blast < -10)
       {
        game->bullets[i].dead = 2;
        game->bullets[i].blast=0;
        game->bullets[i].x=-2;
        game->bullets[i].y=-2;
       }
       if(collidebull(game,i)==2)
    {
        game->enemy.life -= 3;
    }
    if(((game->bullets[i].x-game->screen<-(game->screen)) &&(game->bullets[i].x != -2)) || game->bullets[i].x-game->screen>-(game->screen)+1300)
        {
            game->bullets[i].dead=2;
            game->bullets[i].blast=0;
            game->bullets[i].x=-2;
            game->bullets[i].y=-2;
        }


  }


  for(i=0;i<100;i++)
   {
      if(game->ebullet[i].x >0 && game->ebullet[i].y>0 && game->ebullet[i].dead==2)
      {
       if(game->ebullet[i].dir == 0)
        game->ebullet[i].x-= 10;
       else
        game->ebullet[i].x+= 10;

      }
   }
  game->enemy.x += game->enemy.dx;
  game->enemy.y += game->enemy.dy;
  game->enemy.dy += grav;
  game->etime += 1;
  for(i=0;i<100;i++)
  {
      if(game->bomb[i].dead == 0)
        game->bomb[i].x = game->bomb[i].x -10;
  }

  for(i=0;i<100;i++)
  {
      if(ebcollide(game,i)==4 || ebcollide(game,i)==2 || ebcollide(game,i)==3 || ebcollide(game,i)==1)
      {
       game->ebullet[i].dead = 1;
       game->ebullet[i].blast -= 1;
      }
      if(game->ebullet[i].blast < 0)
        game->ebullet[i].blast -= 1;
      if(game->ebullet[i].blast < -10)
       {
        game->ebullet[i].dead = 2;
        game->ebullet[i].blast=0;
        game->ebullet[i].x=-2;
        game->ebullet[i].y=-2;
       }
        if(ebcollide(game,i)==2)
    {
        game->dog.life -= 3;
    }
    if(((game->ebullet[i].x-game->screen<-(game->screen)) &&(game->ebullet[i].x != -2)) || game->ebullet[i].x-game->screen>-(game->screen)+1300)
        {
            game->ebullet[i].dead=2;
            game->ebullet[i].blast=0;
            game->ebullet[i].x=-2;
            game->ebullet[i].y=-2;
        }

  }
  if(game->enemy.life<=0)
  {
      for(i=0;i<100;i++)
       {
           game->ebullet[i].x =-2;
           game->ebullet[i].y =-2;
        }
        game->enemy.dead+=1;
        q=6;
        if(game->enemy.dead > 100)
        {
        game->enemy.dx=0;
        game->enemy.dy=0;
        game->enemy.x=game->dog.x;
        game->enemy.y=game->dog.y+1000;
        }
  }

  if(game->dog.life <=0)
  {
      for(i=0;i<100;i++)
       {
           game->bullets[i].x = -2;
           game->bullets[i].y = -2;
        }
        game->dog.dead += 1;
        r=6;
        if(game->dog.dead > 100)
        {
        game->dog.dx=0;
        game->dog.dy=0;
        game->dog.x=game->enemy.x;
        game->dog.y=game->enemy.y+1000;
        }
  }

   if(game->dog.y>800)
   {
       game->dog.life=0;
       game->dog.dx=0;
       game->dog.dy=0;
       game->dog.x=game->enemy.x;
       game->dog.y=game->enemy.y+1000;
   }


   if(game->enemy.y>800)
   {
       game->enemy.life=0;
       game->enemy.dx=0;
       game->enemy.dy=0;
       game->enemy.x=game->dog.x;
       game->enemy.y=game->dog.y+1000;
   }
   if(game->gametime%30 ==0)
    {
     for(i=0;i<100;i++)
     {
       if(game->target[i].x-game->screen>-(game->screen) && game->target[i].x-game->screen<-(game->screen)+1100)
            addbullet(game,i);
     }
    }

    game->gametime+=1;
}

int main(int argc,char *argv[])
{
    SDL_Window *window;

    SDL_Renderer *renderer;
    game game;
    int i;

    game.gametime=0;
    game.dog.count =10;
    game.enemy.count =10;
    game.screen =0;
    int done=1;
    game.dog.x = 100;
    game.enemy.x = 150;
    game.dog.y = 450;
    game.enemy.y = 450;
    game.dog.bools = 0;
    game.enemy.bools = 0;
    game.dog.dx=0;
    game.enemy.dx =0 ;
    game.dog.dy = 0;
    game.enemy.dy = 0;
    game.counts = 0;
    game.ecounts =0;
    game.time = 1;
    game.etime = 1;
    game.dog.doubles=0;
    game.enemy.doubles =0;
    game.enemy.life = 600;
    game.dog.life = 600;
    game.dog.dead=0;
    game.enemy.dead=0;
    game.bullno=0;
    for(i=0;i<101;i++)
    {
        if(i==2)
            continue;
    game.brick[i].ix = 300;
    game.brick[i].iy =60;
    game.brick[i].x=i*300;
    game.brick[i].y=650;
    }
    for(i=0;i<100;i++)
    {
    game.bullets[i].ix = 92;
    game.bullets[i].iy = 59;
    game.bullets[i].x = 0;
    game.bullets[i].y = 0;
    game.bullets[i].blast = 0;
    game.bullets[i].dead = 2;
    }
    for(i=0;i<100;i++)
    {
    game.ebullet[i].ix = 92;
    game.ebullet[i].iy = 59;
    game.ebullet[i].x = 0;
    game.ebullet[i].y = 0;
    game.ebullet[i].blast = 0;
    game.ebullet[i].dead = 2;
    game.target[i].life=200;
    game.target[i].dead =1;
    }

    for(i=0;i<100;i++)
    {
        game.bomb[i].ix=40;
        game.bomb[i].iy=20;
        game.bomb[i].dead =1;
    }


    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    window=SDL_CreateWindow("The Dog",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1200,700,0);
    SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    r=0;
    q=0;
    render(renderer,&game);
    game.dog.ix=120/3;
    game.enemy.ix = 120/3;
    game.dog.iy=209/3;
    game.enemy.iy=209/3;
    game.dahealth.x=100;
    game.dahealth.y=50;
    game.dahealth.ix=8;
    game.dahealth.iy=30;
    game.enemyhealth.x=710;
    game.enemyhealth.y=50;
    game.enemyhealth.ix=8;
    game.enemyhealth.iy=30;
    print(renderer,&game,0,5);


    while(done==1)
    {

        done=events(renderer,&game);
        game.dog.bools=0;
        game.enemy.bools =0;
        process(&game);
        collide(&game);
        ecollide(&game);
        print(renderer,&game,r,q);
    }


    SDL_DestroyTexture(game.bricks);
    for(i=0;i<7;i++)
    {
        SDL_DestroyTexture(game.texture[i]);
    }
    for(i=0;i<7;i++)
    {
        SDL_DestroyTexture(game.etexture[i]);
    }
    SDL_DestroyTexture(game.ebullets);
    SDL_DestroyTexture(game.blast);
    SDL_DestroyTexture(game.sky);
    SDL_DestroyTexture(game.dahp);
    SDL_DestroyTexture(game.daname);
    SDL_DestroyTexture(game.enemyname);
    SDL_DestroyTexture(game.targets);
    SDL_DestroyTexture(game.bombs);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
}
