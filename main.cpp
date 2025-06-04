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

// Lighting controls
bool mainLightOn = true;
bool leftLightOn = true;
bool rightLightOn = true;
bool projectorOn = true;
bool showAirConditioners = true;
bool windowOpen = false;  // Cửa sổ đang mở hay đóng

// Mouse controls
int mouseX, mouseY;
bool mousePressed = false;

// Light positions
GLfloat mainLightPos[] = { 0.0f, 8.0f, 0.0f, 1.0f };
GLfloat leftLightPos[] = { -6.0f, 8.0f, 2.0f, 1.0f };
GLfloat rightLightPos[] = { 6.0f, 8.0f, 2.0f, 1.0f };
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

void drawDesk() {
    // Desktop
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f);
    drawBox(1.2f, 0.05f, 0.8f);
    glPopMatrix();

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

void drawChair() {
    // Seat
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
    glPushMatrix();
    glTranslatef(0.0f, 0.3f, 0.0f);
    drawBox(0.4f, 0.05f, 0.4f);
    glPopMatrix();

    // Backrest
    glPushMatrix();
    glTranslatef(0.0f, 0.44f, 0.2f);
    drawBox(0.4f, 0.3f, 0.05f);
    glPopMatrix();

    // Legs
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, darkGray);
    // Front left leg
    glPushMatrix();
    glTranslatef(-0.15f, 0.0f, 0.15f);
    drawBox(0.03f, 0.6f, 0.03f);
    glPopMatrix();

    // Front right leg
    glPushMatrix();
    glTranslatef(0.15f, 0.0f, 0.15f);
    drawBox(0.03f, 0.6f, 0.03f);
    glPopMatrix();

    // Back left leg
    glPushMatrix();
    glTranslatef(-0.15f, 0.0f, -0.15f);
    drawBox(0.03f, 0.6f, 0.03f);
    glPopMatrix();

    // Back right leg
    glPushMatrix();
    glTranslatef(0.15f, 0.0f, -0.15f);
    drawBox(0.03f, 0.6f, 0.03f);
    glPopMatrix();
}

void drawBlackboard() {
    // Green board
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, -7.8f);
    drawBox(6.0f, 2.0f, 0.1f);
    glPopMatrix();

    // Black writing area
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, -7.75f);
    drawBox(5.5f, 1.5f, 0.05f);
    glPopMatrix();

    // Frame
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, -7.85f);
    drawBox(6.2f, 0.1f, 0.1f);
    glPopMatrix();
}

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
    drawBox(16.0f, 2.0f, 0.2f);
    glPopMatrix();

    // Trên
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wallTop);
    glPushMatrix();
    glTranslatef(0.0f, 5.0f, -8.0f);
    drawBox(16.0f, 6.0f, 0.2f);
    glPopMatrix();

    // ==== TƯỜNG TRÁI ====
    // Dưới
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wallBottom);
    glPushMatrix();
    glTranslatef(-8.0f, 1.0f, 0.0f);
    drawBox(0.2f, 2.0f, 16.0f);
    glPopMatrix();

    // Trên
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wallTop);
    glPushMatrix();
    glTranslatef(-8.0f, 5.0f, 0.0f);
    drawBox(0.2f, 6.0f, 16.0f);
    glPopMatrix();

    // ==== TƯỜNG PHẢI ====
    // Dưới
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wallBottom);
    glPushMatrix();
    glTranslatef(8.0f, 1.0f, 0.0f);
    drawBox(0.2f, 2.0f, 16.0f);
    glPopMatrix();

    // Trên
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wallTop);
    glPushMatrix();
    glTranslatef(8.0f, 5.0f, 0.0f);
    drawBox(0.2f, 6.0f, 16.0f);
    glPopMatrix();

    // ==== CỬA SỔ TRÊN TƯỜNG TRÁI ====
    // Cửa sổ mở được
    for (int i = 0; i < 4; i++) {
        drawWindowPair(-7.9f, 4.0f, -4.0f + i * 2.5f);
    }

    // ==== ĐIỀU HÒA (nếu bật) ====
    if (showAirConditioners) {
        drawAirConditioner(-7.8f, 6.5f, -2.0f);
        drawAirConditioner(-7.8f, 6.5f, 2.0f);
    }
}

void drawWallPicture(float x, float y, float z) {
    GLfloat frameColor[] = { 0.4f, 0.2f, 0.1f, 1.0f };  // khung gỗ
    GLfloat picColor[] = { 0.8f, 0.9f, 1.0f, 1.0f };    // nội dung tranh

    glPushMatrix();
    glTranslatef(x, y, z);

    // Vẽ khung tranh
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, frameColor);
    drawBox(2.0f, 1.0f, 0.05f);

    // Vẽ bức tranh bên trong có texture chữ
    glTranslatef(0.0f, 0.0f, -0.01f);

    // Bật texture chữ
    glEnable(GL_TEXTURE_2D);

    // Vẽ hộp tranh với texture
    glBegin(GL_QUADS);
    // Mặt trước của hộp tranh (chiều ngang 0.9, dọc 0.5)
    glTexCoord2f(0, 0); glVertex3f(-0.45f, -0.25f, 0.01f);
    glTexCoord2f(1, 0); glVertex3f(0.45f, -0.25f, 0.01f);
    glTexCoord2f(1, 1); glVertex3f(0.45f, 0.25f, 0.01f);
    glTexCoord2f(0, 1); glVertex3f(-0.45f, 0.25f, 0.01f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void drawWallClock(float x, float y, float z) {
    GLUquadric* quad = gluNewQuadric();
    GLfloat clockColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };   // nền trắng
    GLfloat borderColor[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // viền đen

    glPushMatrix();
    glTranslatef(x, y, z);

    // Viền đồng hồ
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, borderColor);
    gluDisk(quad, 0.19f, 0.2f, 30, 1);

    // Nền mặt đồng hồ
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, clockColor);
    gluDisk(quad, 0.0f, 0.19f, 30, 1);

    // Kim giờ và phút (tĩnh)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, borderColor);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.01f); glVertex3f(0.0f, 0.15f, 0.01f); // phút
    glVertex3f(0.0f, 0.0f, 0.01f); glVertex3f(0.1f, 0.0f, 0.01f);  // giờ
    glEnd();

    glPopMatrix();
    gluDeleteQuadric(quad);
}




void drawCabinets() {
    // Right side cabinets
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glTranslatef(7.0f, 1.5f, -6.0f + i * 2.0f);
        drawBox(1.5f, 3.0f, 1.8f);
        glPopMatrix();
    }
}



void drawAirConditioner(float x, float y, float z) {
    GLfloat acColor[] = { 0.8f, 0.85f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, acColor);

    glPushMatrix();
    glTranslatef(x, y, z);
    drawBox(1.0f, 0.5f, 2.0f); // điều hòa hình hộp dài

    glPopMatrix();
}



void drawWindowPair(float x, float y, float z) {
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);

    // Cánh trái (đứng yên)
    glPushMatrix();
    glTranslatef(x, y, z);
    drawBox(0.05f, 2.0f, 0.7f);
    glPopMatrix();

    // Cánh phải (xoay khi mở)
    glPushMatrix();
    glTranslatef(x, y, z + 0.8f);
    if (windowOpen) {
        glTranslatef(0.0f, 0.0f, -0.35f);
        glRotatef(-60.0f, 0, 1, 0);
        glTranslatef(0.0f, 0.0f, 0.35f);
    }
    drawBox(0.05f, 2.0f, 0.7f);
    glPopMatrix();
}


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

void setupLighting() {
    glEnable(GL_LIGHTING);

    // Main ceiling light (GL_LIGHT0)
    if (mainLightOn) {
        glEnable(GL_LIGHT0);
        GLfloat mainAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
        GLfloat mainDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
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
        GLfloat leftAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat leftDiffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
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
        GLfloat rightDiffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
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
    // Tranh trên tường bên trái
    drawWallPicture(-6.0f, 4.0f, -7.8f);  // (X, Y, Z)
   
    // Đồng hồ trên tường trước
    drawWallClock(0.0f, 7.0f, -7.8f);    // (X, Y, Z)

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

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        mainLightOn = !mainLightOn;
        std::cout << "Main light: " << (mainLightOn ? "ON" : "OFF") << std::endl;
        break;
    case '2':
        leftLightOn = !leftLightOn;
        std::cout << "Left light: " << (leftLightOn ? "ON" : "OFF") << std::endl;
        break;
    case '3':
        rightLightOn = !rightLightOn;
        std::cout << "Right light: " << (rightLightOn ? "ON" : "OFF") << std::endl;
        break;
    case '4':
        projectorOn = !projectorOn;
        std::cout << "Projector: " << (projectorOn ? "ON" : "OFF") << std::endl;
        break;

    case '5':
        showAirConditioners = !showAirConditioners;
        std::cout << "Air conditioners: " << (showAirConditioners ? "ON" : "OFF") << std::endl;
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

    case 'c':
    case 'C':
        windowOpen = !windowOpen;
        std::cout << "Windows: " << (windowOpen ? "Opened" : "Closed") << std::endl;
        break;

    case 27: // ESC key
        exit(0);
        break;
    }
    glutPostRedisplay();
}

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
    std::cout << "1: Toggle main ceiling light" << std::endl;
    std::cout << "2: Toggle left area light" << std::endl;
    std::cout << "3: Toggle right area light" << std::endl;
    std::cout << "4: Toggle projector light" << std::endl;
    std::cout << "5: Toggle air conditioners" << std::endl;

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
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}