#include "../raylib/src/raylib.h"
#include <math.h>
#include <stdio.h>

#define SCREEN_WIDTH 2000
#define SCREEN_HEIGHT 1100
#define SCREEN_TITLE "....."
#define BALL_SIZE 10
#define NUM_BALLS 500
#define SPEED 200
#define NUM_COLORS 3
Color colors[] = {
    GOLD,
    RED,
    BLUE,
};

typedef struct Ball {
    float x;
    float y;
    float sx;
    float sy;
    Color color;
} Ball;

Ball balls[NUM_BALLS];

static inline float distance(Ball b1, Ball b2) {
    float a = b2.x - b1.x;
    float as = a * a;
    float b = b2.y - b1.y;
    float bs = b * b;
    return sqrt(as + bs);
}

bool ballCollides(Ball b1, Ball b2) {
    return 2 * BALL_SIZE > distance(b1, b2);
}


void updateAfterCollision(Ball *ball) {
    ball -> color = GREEN;
    ball -> sx *= -1;
    ball -> sy *= -1;
}

int checkCollission(Ball ball, int items, int exclude) {
    int r = -1;
    for (int i = 0; i<items; i++) {
        if(i == exclude) continue;
        if (ballCollides(balls[i], ball)){
            updateAfterCollision(&balls[i]);
            r = 1;
        }
    }

    return r;
}

void randomBalls()
{
    for (int i = 0; i < NUM_BALLS; i++)
    {
        Ball ball = {0, 0};
        ball.x = GetRandomValue(BALL_SIZE, SCREEN_WIDTH - BALL_SIZE);
        ball.y = GetRandomValue(BALL_SIZE, SCREEN_HEIGHT - BALL_SIZE);
        ball.sx = GetRandomValue(-200, 200);
        ball.sy = GetRandomValue(-200, 200);
        ball.color = BLUE;
        int c = checkCollission(ball, i, -1);
        if (c != -1) {
            updateAfterCollision(&ball);
        }
        balls[i] = ball;
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    SetTargetFPS(60);

    randomBalls();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyPressed(KEY_ENTER))
        {
            randomBalls();
        }

        for (int i = 0; i < NUM_BALLS; i++)
        {
            Ball ball = balls[i];

            ball.y += ball.sy * GetFrameTime();
            ball.x += ball.sx * GetFrameTime();


            if (ball.y - BALL_SIZE <= 0 || ball.y + BALL_SIZE >= SCREEN_HEIGHT)
             {
                 ball.sy *= -1;
             }

            if (ball.x - BALL_SIZE <= 0 || ball.x + BALL_SIZE >= SCREEN_WIDTH)
             {
                 ball.sx *= -1;
             }


            if (checkCollission(ball, NUM_BALLS, i) != -1) {
                updateAfterCollision(&ball);
            }


            balls[i] = ball;
            DrawCircle(ball.x, ball.y, BALL_SIZE, ball.color);

        }

        EndDrawing();
    }

    return 0;
}
