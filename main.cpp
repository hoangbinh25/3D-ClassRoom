#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <vector>

void drawAirConditioner(float x, float y, float z);
void drawWindowPair(float x, float y, float z);

// Camera controls
float cameraX = 0.0f, cameraY = 5.0f, cameraZ = 15.0f;
float cameraAngleX = -20.0f, cameraAngleY = 0.0f;
bool fanOn = true;               // Bật/tắt quạt


// Lighting controls
bool mainLightOn = false;
bool leftLightOn = false;
bool rightLightOn = false;
bool projectorOn = false;
float fanAngle = 0.0f;           // Góc quay của cánh quạt 

// Mouse controls
int mouseX, mouseY;
bool mousePressed = false;

// Light positions
GLfloat mainLightPos[] = { 0.0f, 7.0f, 0.0f, 1.0f };
GLfloat leftLightPos[] = { 6.0f, .0f, 2.0f, 1.0f };
GLfloat rightLightPos[] = { -6.0f, 7.0f, 2.0f, 1.0f };
GLfloat projectorPos[] = { 0.0f, 7.5f, 8.0f, 1.0f };

// Colors
GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightGray[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat darkGray[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat brown[] = { 0.6f, 0.4f, 0.2f, 1.0f };
GLfloat green[] = { 0.2f, 0.6f, 0.3f, 1.0f };
GLfloat darkGreen[] = { 0.1f, 0.4f, 0.2f, 1.0f };
GLfloat black[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat blue[] = { 0.3f, 0.5f, 0.8f, 1.0f };

GLfloat wallTop[] = { 0.97f, 0.97f, 0.97f, 1.0f };     // trắng kem
GLfloat wallBottom[] = { 0.75f, 0.85f, 0.9f, 1.0f };   // xanh nhạt

// Thực thể vẽ hình hộp chữ nhật
void drawBox(float width, float height, float depth) {
    glBegin(GL_QUADS);

    // Front face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-width / 2, -height / 2, depth / 2);
    glVertex3f(width / 2, -height / 2, depth / 2);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);

    // Back face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, -depth / 2);

    // Top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);

    // Bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, depth / 2);
    glVertex3f(-width / 2, -height / 2, depth / 2);

    // Right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(width / 2, -height / 2, depth / 2);

    // Left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(-width / 2, -height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, -depth / 2);

    glEnd();
}

// Vẽ bàn
void drawDesk() {
    // Mặt bàn
    // Desktop
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f);
    drawBox(1.2f, 0.05f, 0.8f);
    glPopMatrix();

    // Các chân bàn
    // Legs
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, darkGray);
    // Front left leg
    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, 0.3f);
    drawBox(0.05f, 0.8f, 0.05f);
    glPopMatrix();

    // Front right leg
    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 0.3f);
    drawBox(0.05f, 0.8f, 0.05f);
    glPopMatrix();

    // Back left leg
    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, -0.3f);
    drawBox(0.05f, 0.8f, 0.05f);
    glPopMatrix();

    // Back right leg
    glPushMatrix();
    glTranslatef(0.5f, 0.0f, -0.3f);
    drawBox(0.05f, 0.8f, 0.05f);
    glPopMatrix();
}

// Vẽ ghế
void drawChair() {
    // Mặt ghế
    // Seat
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
    glPushMatrix();
    glTranslatef(0.0f, 0.06f, 0.0f);
    drawBox(0.4f, 0.05f, 0.4f);
    glPopMatrix();

    // Tựa lưng
    // Backrest
    glPushMatrix();
    glTranslatef(0.0f, 0.20f, 0.2f);
    drawBox(0.4f, 0.3f, 0.05f);
    glPopMatrix();

    // Các chân gghế
    // Legs
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, darkGray);
    // Front left leg
    glPushMatrix();
    glTranslatef(-0.15f, -0.15f, 0.15f);
    drawBox(0.03f, 0.4f, 0.03f);
    glPopMatrix();

    // Front right leg
    glPushMatrix();
    glTranslatef(0.15f, -0.15f, 0.15f);
    drawBox(0.03f, 0.4f, 0.03f);
    glPopMatrix();

    // Back left leg
    glPushMatrix();
    glTranslatef(-0.15f, -0.15f, -0.15f);
    drawBox(0.03f, 0.4f, 0.03f);
    glPopMatrix();

    // Back right leg
    glPushMatrix();
    glTranslatef(0.15f, -0.15f, -0.15f);
    drawBox(0.03f, 0.4f, 0.03f);
    glPopMatrix();
}

// Vẽ bảng
void drawBlackboard() {
    // Phần xanh bao quanh
    // Green board
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, -7.8f);
    drawBox(6.0f, 2.0f, 0.1f);
    glPopMatrix();

    // Phần bảng đen
    // Black writing area
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, -7.75f);
    drawBox(5.5f, 1.5f, 0.05f);
    glPopMatrix();

    // Phần khung màu nâu ở dưới
    // Frame
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, -7.85f);
    drawBox(6.2f, 0.1f, 0.1f);
    glPopMatrix();
}

// Vẽ trần nhà
void drawCeiling() {
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    glPushMatrix();
    glTranslatef(0.0f, 8.5f, 0.0f);
    drawBox(16.0f, 0.2f, 16.0f);
    glPopMatrix();

    // Ceiling lights (grid pattern)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lightGray);
    for (int i = -6; i <= 6; i += 3) {
        for (int j = -6; j <= 6; j += 3) {
            glPushMatrix();
            glTranslatef(i, 8.3f, j);
            drawBox(1.5f, 0.1f, 1.5f);
            glPopMatrix();
        }
    }
}


// Vẽ máy tính
void drawComputer() {

    GLUquadric* quad = gluNewQuadric();

    // Màu sắc
    GLfloat black[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat gray[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat darkGray[] = { 0.2f, 0.2f, 0.2f, 1.0f };

    // === Màn hình ===
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
    glTranslatef(0.0f, 0.65f, -0.1f); // nằm trên bàn
    drawBox(0.4f, 0.4f, 0.05f); // thân màn hình

    // Chân đế màn hình
    glTranslatef(0.0f, -0.25f, 0.0f);
    drawBox(0.1f, 0.05f, 0.05f);
    glTranslatef(0.0f, -0.02f, 0.0f);
    drawBox(0.2f, 0.01f, 0.1f); // đế chân
    glPopMatrix();

    // === Thùng máy (case) ===
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, darkGray);
    glTranslatef(0.4f, 0.0f, 0.0f); // dưới bàn hoặc bên cạnh
    drawBox(0.15f, 0.5f, 0.4f);
    glPopMatrix();

    // === Bàn phím ===
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
    glTranslatef(0.0f, 0.42f, 0.2f); // trên mặt bàn
    drawBox(0.35f, 0.02f, 0.15f);
    glPopMatrix();

    // === Chuột ===
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
    glTranslatef(0.25f, 0.42f, 0.25f);
    drawBox(0.05f, 0.02f, 0.08f);
    glPopMatrix();


    // === LOA TRÁI ===
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, darkGray);
    glTranslatef(-0.25f, 0.45f, -0.1f); // bên trái màn hình
    drawBox(0.05f, 0.25f, 0.05f);
    glPopMatrix();

    // === LOA PHẢI ===
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, darkGray);
    glTranslatef(0.25f, 0.45f, -0.1f); // bên phải màn hình
    drawBox(0.05f, 0.25f, 0.05f);
    glPopMatrix();

    // === CAMERA ===
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
    glTranslatef(0.0f, 0.88f, -0.125f); // trên đầu màn hình
    drawBox(0.08f, 0.03f, 0.02f); // thân camera

    // Ống kính camera
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
    glTranslatef(0.0f, 0.0f, 0.015f); // mặt trước camera
    gluSphere(quad, 0.01f, 10, 10);
    glPopMatrix();

    gluDeleteQuadric(quad);

}

// Vẽ tường
void drawWalls() {
    // ==== SÀN LÁT GẠCH CARO ====
    float tileSize = 2.0f;
    for (float x = -8.0f; x < 8.0f; x += tileSize) {
        for (float z = -8.0f; z < 8.0f; z += tileSize) {
            bool even = static_cast<int>((x + 8) / tileSize + (z + 8) / tileSize) % 2 == 0;

            if (even)
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lightGray);
            else
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, darkGray);

            glPushMatrix();
            glTranslatef(x + tileSize / 2.0f, -0.5f, z + tileSize / 2.0f);
            drawBox(tileSize, 0.2f, tileSize);
            glPopMatrix();
        }
    }

    // ==== TƯỜNG SAU: chia trên/dưới ====
    // Dưới (chân tường)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wallBottom);
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, -8.0f);
    drawBox(16.0f, 3.0f, 0.1f);
    glPopMatrix();

    // Trên
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wallTop);
    glPushMatrix();
    glTranslatef(0.0f, 5.0f, -8.0f);
    drawBox(16.0f, 7.0f, 0.2f);
    glPopMatrix();

    // ==== TƯỜNG TRÁI ====
    // Dưới
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wallBottom);
    glPushMatrix();
    glTranslatef(-8.0f, 1.0f, 0.0f);
    drawBox(0.1f, 3.0f, 16.0f);
    glPopMatrix();

    // Trên
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wallTop);
    glPushMatrix();
    glTranslatef(-8.0f, 5.0f, 0.0f);
    drawBox(0.2f, 7.0f, 16.0f);
    glPopMatrix();

    // ==== TƯỜNG PHẢI ====
    // Dưới
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wallBottom);
    glPushMatrix();
    glTranslatef(8.0f, 1.0f, 0.0f);
    drawBox(0.1f, 3.0f, 16.0f);
    glPopMatrix();

    // Trên
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wallTop);
    glPushMatrix();
    glTranslatef(8.0f, 5.0f, 0.0f);
    drawBox(0.2f, 7.0f, 16.0f);
    glPopMatrix();

    // ==== CỬA SỔ TRÊN TƯỜNG TRÁI ====
    for (int i = 0; i < 4; i++) {
        drawWindowPair(-7.9f, 4.0f, -4.0f + i * 2.5f);
    }
}

// Vẽ đồng hồ
void drawWallClock(float x, float y, float z) {
    GLUquadric* quad = gluNewQuadric();
    GLfloat clockColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };   // nền trắng
    GLfloat borderColor[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // viền đen

    glPushMatrix();
    glTranslatef(x, y, z);

    // Viền đồng hồ
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, borderColor);
    gluDisk(quad, 0.34f, 0.4f, 30, 1);

    // Nền mặt đồng hồ
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, clockColor);
    gluDisk(quad, 0.0f, 0.4f, 30, 1);

    // Kim giờ và phút (tĩnh)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, borderColor);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.01f); glVertex3f(0.0f, 0.30f, 0.01f); // phút
    glVertex3f(0.0f, 0.0f, 0.01f); glVertex3f(0.2f, 0.0f, 0.01f);  // giờ
    glEnd();

    glPopMatrix();
    gluDeleteQuadric(quad);
}

// Vẽ tủ
void drawCabinetWithFrontDoors() {
    // Kích thước tủ
    float width = 2.0f;
    float height = 4.0f;
    float depth = 1.5f;

    // Vẽ thân tủ
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
    drawBox(width, height, depth);

    // Cửa tủ nằm ở mặt trước
    float doorThickness = 0.05f;
    float doorWidth = width / 2.0f;
    float doorHeight = height;
    float doorZ = depth / 2.0f + doorThickness / 2.0f; // nằm ngoài mặt trước

    // Vẽ 2 cánh cửa
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);

    // Cửa trái
    glPushMatrix();
    glTranslatef(-doorWidth / 2.0f, 0.0f, doorZ);
    drawBox(doorWidth, doorHeight, doorThickness);
    glPopMatrix();

    // Cửa phải
    glPushMatrix();
    glTranslatef(doorWidth / 2.0f, 0.0f, doorZ);
    drawBox(doorWidth, doorHeight, doorThickness);
    glPopMatrix();

    // Tay nắm cửa hướng ra phía bàn học (mặt trước)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, darkGray);
    float handleWidth = 0.05f;
    float handleHeight = 0.25f;
    float handleDepth = 0.05f;
    float handleOffsetX = 0.25f;

    // Tay nắm cửa trái (nằm gần mép phải của cửa trái)
    glPushMatrix();
    glTranslatef(-doorWidth / 2.0f + handleOffsetX, 0.0f, doorZ + handleDepth / 2.0f);
    drawBox(handleWidth, handleHeight, handleDepth);
    glPopMatrix();

    // Tay nắm cửa phải (nằm gần mép trái của cửa phải)
    glPushMatrix();
    glTranslatef(doorWidth / 2.0f - handleOffsetX, 0.0f, doorZ + handleDepth / 2.0f);
    drawBox(handleWidth, handleHeight, handleDepth);
    glPopMatrix();
}

// Gọi lại hàm drawCabinetWithFrontDoors() và dùng vòng for để vẽ nhiều tủ
void drawCabinets() {
    // Right side cabinets
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(7.0f, 1.5f, -6.0f + i * 2.5f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        drawCabinetWithFrontDoors();
        glPopMatrix();
    }
}

// Vẽ điều hòa
void drawAirConditioner(float x, float y, float z) {
    GLfloat acColor[] = { 0.8f, 0.85f, 0.9f, 1.0f };     // Màu thân điều hòa
    GLfloat bevelColor[] = { 0.75f, 0.8f, 0.85f, 1.0f }; // Màu cạnh vát

    glPushMatrix();
    glTranslatef(x, y, z);

    // --- Vẽ thân chính (nhỏ hơn một chút để tạo không gian cho phần vát) ---
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, acColor);
    drawBox(0.9f, 0.4f, 1.8f);

    // --- Vẽ các phần vát cạnh bằng các hình hộp mỏng hơn ---
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, bevelColor);

    float bevelThickness = 0.05f;

    // Trên - trái
    glPushMatrix();
    glTranslatef(-0.45f, 0.2f, 0.0f);
    drawBox(bevelThickness, bevelThickness, 1.8f);
    glPopMatrix();

    // Trên - phải
    glPushMatrix();
    glTranslatef(0.45f, 0.2f, 0.0f);
    drawBox(bevelThickness, bevelThickness, 1.8f);
    glPopMatrix();

    // Dưới - trái
    glPushMatrix();
    glTranslatef(-0.45f, -0.2f, 0.0f);
    drawBox(bevelThickness, bevelThickness, 1.8f);
    glPopMatrix();

    // Dưới - phải
    glPushMatrix();
    glTranslatef(0.45f, -0.2f, 0.0f);
    drawBox(bevelThickness, bevelThickness, 1.8f);
    glPopMatrix();

    // Trước - trái
    glPushMatrix();
    glTranslatef(-0.45f, 0.0f, 0.9f);
    drawBox(bevelThickness, 0.4f, bevelThickness);
    glPopMatrix();

    // Trước - phải
    glPushMatrix();
    glTranslatef(0.45f, 0.0f, 0.9f);
    drawBox(bevelThickness, 0.4f, bevelThickness);
    glPopMatrix();

    // Sau - trái
    glPushMatrix();
    glTranslatef(-0.45f, 0.0f, -0.9f);
    drawBox(bevelThickness, 0.4f, bevelThickness);
    glPopMatrix();

    // Sau - phải
    glPushMatrix();
    glTranslatef(0.45f, 0.0f, -0.9f);
    drawBox(bevelThickness, 0.4f, bevelThickness);
    glPopMatrix();

    glPopMatrix();
}

void drawCeilingAirConditioner(float x, float y, float z) {
    GLfloat bodyColor[] = { 0.9f, 0.9f, 0.95f, 1.0f };     // Màu thân máy
    GLfloat ventColor[] = { 0.7f, 0.7f, 0.8f, 1.0f };      // Màu khe gió

    glPushMatrix();
    glTranslatef(x, y, z);

    // --- Thân điều hòa âm trần (ốp sát trần) ---
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, bodyColor);
    drawBox(1.5f, 0.1f, 1.5f); // Hộp vuông mỏng

    // --- Khe gió xung quanh 4 cạnh ---
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ventColor);

    float ventLength = 1.0f;
    float ventWidth = 0.05f;
    float ventDepth = 0.02f;

    // Khe trước
    glPushMatrix();
    glTranslatef(0.0f, -0.05f, 0.55f);
    drawBox(ventLength, ventDepth, ventWidth);
    glPopMatrix();

    // Khe sau
    glPushMatrix();
    glTranslatef(0.0f, -0.05f, -0.55f);
    drawBox(ventLength, ventDepth, ventWidth);
    glPopMatrix();

    // Khe trái
    glPushMatrix();
    glTranslatef(-0.55f, -0.05f, 0.0f);
    drawBox(ventWidth, ventDepth, ventLength);
    glPopMatrix();

    // Khe phải
    glPushMatrix();
    glTranslatef(0.55f, -0.05f, 0.0f);
    drawBox(ventWidth, ventDepth, ventLength);
    glPopMatrix();

    // --- (Tùy chọn) Miếng che ở giữa hoặc logo ---
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, bodyColor);
    glPushMatrix();
    glTranslatef(0.0f, -0.045f, 0.0f);
    drawBox(0.4f, 0.01f, 0.4f); // mặt che trung tâm
    glPopMatrix();

    glPopMatrix();
}

// Vẽ quạt trần
void drawCeilingFan(float x, float y, float z, float scale) {
    GLfloat rodColor[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat motorColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat bladeColor[] = { 0.6f, 0.6f, 0.6f, 1.0f };

    glPushMatrix();
    glTranslatef(x, y, z);

    // Tăng giảm kích thước toàn bộ quạt
    glScalef(scale, scale, scale);

    // Vẽ trục quạt (hình hộp dài)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rodColor);
    glPushMatrix();
    glScalef(0.05f, 1.6f, 0.05f);  // Điều chỉnh độ dày và dài của trục
    drawBox(1.0f, 1.0f, 1.0f);
    glPopMatrix();

    // Vẽ motor (hình cầu)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, motorColor);
    glTranslatef(0.0f, -0.8f, 0.0f);  // Đẩy xuống cuối trục
    glutSolidSphere(0.1f, 20, 20);

    // Quay cánh quạt nếu bật
    if (fanOn) {
        fanAngle += 2.0f;  // Tốc độ quay
        if (fanAngle >= 360.0f) fanAngle -= 360.0f;
    }
    glRotatef(fanAngle, 0.0f, 1.0f, 0.0f);  // Quay quanh trục y

    // Vẽ 3 cánh quạt
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, bladeColor);
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glRotatef(i * 120.0f, 0, 1, 0);   // Cánh quạt cách nhau 120 độ
        glTranslatef(0.0f, 0.0f, 0.4f);  // Đẩy cánh quạt ra xa motor
        glScalef(0.15f, 0.02f, 0.6f);    // Thay đổi kích thước cánh quạt (rộng, dày, dài)
        drawBox(1.0f, 1.0f, 1.0f);
        glPopMatrix();
    }

    glPopMatrix();
}

// Vẽ cửa sổ
void drawWindowPair(float x, float y, float z) {
    // Màu khung cửa (gỗ)
    GLfloat frameColor[] = { 0.4f, 0.2f, 0.1f, 1.0f };
    // Màu kính
    GLfloat glassColor[] = { 0.6f, 0.8f, 1.0f, 0.3f }; // xanh nhạt hơi trong mờ

    // === Hàm con vẽ một cánh cửa kính có 4 ô ===
    auto drawGlassPane = [&]() {
        float width = 0.05f;
        float height = 2.0f;
        float depth = 0.7f;

        // Vẽ nền kính
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, glassColor);
        drawBox(width, height, depth);

        // Vẽ thanh chia kính
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, frameColor);

        // Thanh ngang ở giữa
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        drawBox(width + 0.01f, 0.05f, depth);
        glPopMatrix();

        // Thanh dọc ở giữa
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        drawBox(width + 0.01f, height, 0.05f);
        glPopMatrix();
        };

    // === Cánh trái (cố định) ===
    glPushMatrix();
    glTranslatef(x, y, z);
    drawGlassPane();
    glPopMatrix();

    // === Cánh phải (có thể mở) ===
    glPushMatrix();
    glTranslatef(x, y, z + 0.8f);
    drawGlassPane();
    glPopMatrix();
}


// Vẽ máy chiếu
void drawProjector() {
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, darkGray);

    // Thanh treo từ trần xuống
    glPushMatrix();
    glTranslatef(0.0f, 8.0f, 6.0f); // điểm giữa thanh dọc
    drawBox(0.05f, 1.0f, 0.05f);    // thanh mảnh dọc cao 1 đơn vị
    glPopMatrix();

    // Thân máy chiếu
    glPushMatrix();
    glTranslatef(0.0f, 7.5f, 6.0f); // vị trí máy chiếu
    drawBox(0.6f, 0.3f, 0.4f);      // hộp máy chiếu
    glPopMatrix();

}

// Vẽ chậu cây
void drawPottedPlant(float x, float y, float z) {
    GLUquadric* quad = gluNewQuadric();

    // ==== Chậu cây ====
    GLfloat potColor[] = { 0.5f, 0.2f, 0.1f, 1.0f };  // Nâu đất
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, potColor);

    glPushMatrix();
    glTranslatef(x, y + 0.2f, z);     // Chậu đặt trên sàn
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.3f, 0.25f, 0.4f, 16, 16);
    glPopMatrix();

    // ==== Thân cây ====
    GLfloat trunkColor[] = { 0.4f, 0.2f, 0.1f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, trunkColor);

    glPushMatrix();
    glTranslatef(x, y + 0.6f, z);     // Trên chậu
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.05f, 0.05f, 1.0f, 16, 16);
    glPopMatrix();

    // ==== Các tầng tán lá ====
    GLfloat leafColor[] = { 0.0f, 0.6f, 0.2f, 1.0f };  // Xanh lá cây
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, leafColor);

    // Tầng dưới cùng
    glPushMatrix();
    glTranslatef(x, y + 1.1f, z);
    gluSphere(quad, 0.4f, 16, 16);
    glPopMatrix();

    // Tầng giữa
    glPushMatrix();
    glTranslatef(x, y + 1.4f, z);
    gluSphere(quad, 0.3f, 16, 16);
    glPopMatrix();

    // Tầng trên cùng
    glPushMatrix();
    glTranslatef(x, y + 1.65f, z);
    gluSphere(quad, 0.2f, 16, 16);
    glPopMatrix();

    gluDeleteQuadric(quad);
}

// Vẽ Camera
void drawSecurityCamera(float x, float y, float z, float rotateY = 0.0f, float rotateX = 0.0f) {
    GLUquadric* quad = gluNewQuadric();

    GLfloat bodyColor[] = { 0.3f, 0.3f, 0.3f, 1.0f };   // Xám đậm
    GLfloat lensColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };   // Ống kính đen

    // Thân camera (hình hộp)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, bodyColor);
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotateY, 0, 1, 0);         // Quay ngang
    glRotatef(rotateX, 1, 0, 0);         // Quay dọc
    glScalef(0.3f, 0.2f, 0.5f);
    drawBox(1.0f, 1.0f, 1.0f);
    glPopMatrix();

    // Ống kính camera (phía trước)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lensColor);
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotateY, 0, 1, 0);
    glRotatef(rotateX, 1, 0, 0);
    glTranslatef(0.0f, 0.0f, 0.25f);     // phía trước
    gluSphere(quad, 0.05f, 12, 12);
    glPopMatrix();

    gluDeleteQuadric(quad);
}

// Hàm cấu hình ánh sáng không phải thực thể
void setupLighting() {
    glEnable(GL_LIGHTING);

    // Main ceiling light (GL_LIGHT0)
    if (mainLightOn) {
        glEnable(GL_LIGHT0);
        GLfloat mainAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f }; // ánh sáng nền( nhẹ, đều)
        GLfloat mainDiffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f }; // ánh sáng khuếch tán( chiếu từ nguồn sáng)

        glLightfv(GL_LIGHT0, GL_POSITION, mainLightPos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, mainAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, mainDiffuse);
    }
    else {
        glDisable(GL_LIGHT0);
    }

    // Left light (GL_LIGHT1)
    if (leftLightOn) {
        glEnable(GL_LIGHT1);
        GLfloat leftAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };// RGBA (càng gần 1 càng sáng)
        GLfloat leftDiffuse[] = { 0.3f, 0.3f, 0.3f, 1.0f };
        glLightfv(GL_LIGHT1, GL_POSITION, leftLightPos);
        glLightfv(GL_LIGHT1, GL_AMBIENT, leftAmbient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, leftDiffuse);
    }
    else {
        glDisable(GL_LIGHT1);
    }

    // Right light (GL_LIGHT2)
    if (rightLightOn) {
        glEnable(GL_LIGHT2);
        GLfloat rightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat rightDiffuse[] = { 0.3f, 0.3f, 0.3f, 1.0f };
        glLightfv(GL_LIGHT2, GL_POSITION, rightLightPos);
        glLightfv(GL_LIGHT2, GL_AMBIENT, rightAmbient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, rightDiffuse);
    }
    else {
        glDisable(GL_LIGHT2);
    }

    // Đèn máy chiếu chiếu xuống bảng
    if (projectorOn) {
        glEnable(GL_LIGHTING);          
        glEnable(GL_LIGHT3);            // Bật đèn máy chiếu

        GLfloat projAmbient[] = { 1.5f, 1.5f, 1.5f, 1.0f };
        GLfloat projDiffuse[] = { 0.9f, 0.9f, 0.7f, 1.0f };

        // Vị trí đèn: nằm giữa trần nhà, gần bảng (Z âm)
        GLfloat projectorPos[] = { 0.0f, 9.0f, -5.0f, 1.0f };

        // Hướng chiếu: chiếu xuống và hơi nghiêng về bảng
        GLfloat spotDirection[] = { 0.0f, -1.0f, 0.0f };

        glLightfv(GL_LIGHT3, GL_POSITION, projectorPos);
        glLightfv(GL_LIGHT3, GL_AMBIENT, projAmbient);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, projDiffuse);
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotDirection);

        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 25.0f);        // Góc chiếu như hình nón (0-90)
        glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 25.0f);      // Đậm dần ở trung tâm
    }
    else {
        glDisable(GL_LIGHT3);
    }
}

// Thiết lập camera và gọi các hàm vẽ đối tượng/ thực thế (Hàm này không phải thực thể)
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set camera position
    glTranslatef(-cameraX, -cameraY, -cameraZ);
    glRotatef(cameraAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraAngleY, 0.0f, 1.0f, 0.0f);

    setupLighting();

    // === Bàn giáo viên ===
    glPushMatrix();
    glTranslatef(-6.0f, 0.0f, -6.0f); // Bên trái lớp
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // Quay ngược mặt bàn
    glScalef(1.6f, 1.0f, 1.4f); // Bàn to hơn một chút
    drawDesk();
    drawComputer();
    glPopMatrix();

    // === Ghế giáo viên ===
    glPushMatrix();
    glTranslatef(-6.0f, 0.0f, -7.0f); // Sau bàn
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    drawChair();
    glPopMatrix();

    // Draw room components
    drawWalls();
    drawCeiling();
    drawBlackboard();
    drawCabinets();
    drawProjector();
   
    // Đồng hồ trên tường trước
    drawWallClock(0.0f, 7.0f, -7.8f);    // (X, Y, Z)

    // Vẽ cây 
    drawPottedPlant(7.0f, -0.5f, 7.0f);
    

    // Điều hòa âm trần
    drawCeilingAirConditioner(0.0f, 8.2f, 0.0f);
    
    // Camera góc phải trên, chiếu vào giữa lớp
    drawSecurityCamera(7.7f, 8.0f, -7.5f, 320.0f, 40.0f);

    // Quạt trần
    drawCeilingFan(-4.5f, 7.8f, -3.5f, 1.0f); // góc trên trái
    drawCeilingFan(4.5f, 7.8f, -3.5f, 1.0f);  // góc trên phải
    drawCeilingFan(-4.5f, 7.8f, 3.5f, 1.0f);  // góc dưới trái
    drawCeilingFan(4.5f, 7.8f, 3.5f, 1.0f);   // góc dưới phải

    // Draw desks and chairs in rows
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 6; col++) {
            float x = -5.0f + col * 2.0f;
            float z = -2.0f + row * 2.5f;

            // Draw desk
            glPushMatrix();
            glTranslatef(x, 0.0f, z);
            drawDesk();
            glPopMatrix();

            // Draw chair
            glPushMatrix();
            glTranslatef(x, 0.0f, z + 1.0f);
            drawChair();
            glPopMatrix();
        }
    }

    glutSwapBuffers();
}

// Xử lý khi thay đổi kích thước cửa sổ (Không phải thực thể)
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

// Các nút cấu hình bật tắt, di chuyển camera (Không phải thực thể)
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        mainLightOn = !mainLightOn;
        std::cout << "Main light: " << (mainLightOn ? "ON" : "OFF") << std::endl;
        break;
    case '2':
        rightLightOn = !rightLightOn;
        std::cout << "Right light: " << (leftLightOn ? "ON" : "OFF") << std::endl;
        break;
    case '3':
        leftLightOn = !leftLightOn;
        std::cout << "Left light: " << (rightLightOn ? "ON" : "OFF") << std::endl;
        break;
    case '4':
        projectorOn = !projectorOn;
        std::cout << "Projector: " << (projectorOn ? "ON" : "OFF") << std::endl;
        break;

    case 'w':
        cameraZ -= 0.5f;
        break;
    case 's':
        cameraZ += 0.5f;
        break;
    case 'a':
        cameraX -= 0.5f;
        break;
    case 'd':
        cameraX += 0.5f;
        break;
    case 'q':
        cameraY += 0.5f;
        break;
    case 'e':
        cameraY -= 0.5f;
        break;

    case 'f':
    case 'F':
        fanOn = !fanOn;
        break;

    case 27: // ESC key
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// Xử lý sự kiện nhấn chuột
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mousePressed = true;
            mouseX = x;
            mouseY = y;
        }
        else {
            mousePressed = false;
        }
    }
}

void idle() {
    if (fanOn) {
        glutPostRedisplay();
    }
}

// Xử lý kéo chuột, thay đổi góc nhìn camera
void mouseMotion(int x, int y) {
    if (mousePressed) {
        cameraAngleY += (x - mouseX) * 0.5f;
        cameraAngleX += (y - mouseY) * 0.5f;

        // Limit vertical rotation
        if (cameraAngleX > 90.0f) cameraAngleX = 90.0f;
        if (cameraAngleX < -90.0f) cameraAngleX = -90.0f;

        mouseX = x;
        mouseY = y;
        glutPostRedisplay();
    }
}

// Khởi tạo các trạng thái OPENGL
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Material properties
    GLfloat specular[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat shininess[] = { 20.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    std::cout << "=== CLASSROOM 3D CONTROLS ===" << std::endl;
    std::cout << "Mouse: Click and drag to rotate camera" << std::endl;
    std::cout << "WASD: Move camera (W/S: forward/back, A/D: left/right)" << std::endl;
    std::cout << "Q/E: Move camera up/down" << std::endl;
    std::cout << "1: Toggle main ceiling light" << std::endl;   // Ánh sáng cả phòng 
    std::cout << "2: Toggle left area light" << std::endl;
    std::cout << "3: Toggle right area light" << std::endl;
    std::cout << "4: Toggle projector light" << std::endl;

    std::cout << "ESC: Exit" << std::endl;
    std::cout << "=============================" << std::endl;
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("3D Classroom Model - OpenGL");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}