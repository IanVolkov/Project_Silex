#include <iostream>
#include <Time.h>
#include <fstream>
#include "TXLib.h"
#pragma warning (disable:4996)
using namespace std;

// @Author: Kargin Stepan

void Initialization(int xk, int yk, vector<vector<int>>& p, vector <vector<int>>& pp, int situation, int procent) {
    int k;
    for (int i = 0; i <= yk + 1; i++) {
        for (int j = 0; j <= xk + 1; j++) {
            pp[i][j] = p[i][j] = 0;
        }
    }
    if (situation == 0) {
        for (int i = 1; i <= yk; i++) {
            for (int j = 1; j <= xk; j++) {
                if (1 + rand() % 100 > 100 - procent) {
                    k = rand() % 8;
                    pp[i][j] |= (1 << k);
                }
            }
        }
    }
    if (situation == 1) {
        for (int i = 50; i <= 189; i++) {
            for (int j = 161; j <= 300; j++) {
                k = rand() % 8;
                pp[i][j] |= (1 << k);
            }
        }
    }
    if (situation == 2)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 1; j <= 275; j++)
            {
                pp[i + 1][j] |= (1 << 8);
                if (j <= 175)
                {
                    pp[i + 50][j] |= (1 << 8);
                }
            }
        }
        for (int j = 0; j < 5; j++)
        {
            for (int i = 50; i <= yk; i++) pp[i][j + 171] |= (1 << 8);
            for (int i = 0; i <= yk - 70; i++) pp[i][j + 271] |= (1 << 8);
        }
        for (int i = 0; i < 5; i++)
        {
            for (int j = 171; j <= xk; j++) pp[yk - i][j] |= (1 << 8);
            for (int j = 271; j <= xk; j++) pp[yk - 70 - i][j] |= (1 << 8);
        }
        for (int j = 1; j <= 230; j++) {
            for (int i = 6; i < 50; i++) pp[i][j] |= (1 << 0);
        }
    }
    if (situation == 3)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 1; j <= xk; j++)
            {
                pp[34 - i][j] |= (1 << 8);
                if (j <= xk - 76)
                {
                    pp[116 + i][j] |= (1 << 8);
                }
            }
        }
        for (int j = 0; j < 5; j++)
        {
            for (int i = 35; i <= yk; i++)
            {
                pp[i][xk - j] |= (1 << 8);
                if (i >= 121)
                {
                    pp[i][xk - 76 - j] |= (1 << 8);
                }
            }
        }
        for (int i = 35; i <= 115; i++)
        {
            for (int j = 1; j <= 380; j++)
            {
                pp[i][j] |= (1 << 0);
            }
        }
    }
    if (situation == 4)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 1; j <= xk; j++)
            {
                pp[34 - i][j] |= (1 << 8);
                pp[204 + i][j] |= (1 << 8);
            }
        }
        int left = 231, right = 231;
        for (int i = 90; i <= 119; i++)
        {
            for (int j = left; j <= right; j++)
            {
                pp[i][j] |= (1 << 8);
            }
            left--;
            right++;
        }
        int q = 120;
        while (left != right)
        {
            for (int j = left; j <= right; j++)
            {
                pp[q][j] |= (1 << 8);
            }
            left++;
            right--;
            q++;
        }
        for (int j = left; j <= right; j++)
        {
            pp[q][j] |= (1 << 8);
        }
        for (int i = 35; i <= 203; i++)
        {
            for (int j = 1; j <= 150; j++)
            {
                pp[i][j] |= (1 << 0);
            }
        }
    }
    if (situation == 5)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 1; j <= xk; j++)
            {
                pp[34 - i][j] |= (1 << 8);
                pp[204 + i][j] |= (1 << 8);
                if (j <= xk - 116)
                {
                    pp[116 + i][j] |= (1 << 8);
                }
            }
        }
        for (int j = xk - 4; j <= xk; j++)
        {
            for (int i = 35; i <= 203; i++)
            {
                pp[i][j] |= (1 << 8);
            }
        }
        for (int i = 35; i <= 115; i++)
        {
            for (int j = 1; j <= 370; j++)
            {
                pp[i][j] |= (1 << 0);
            }
        }
    }
    if (situation == 6)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 1; j <= xk; j++)
            {
                pp[34 - i][j] |= (1 << 8);
                pp[204 + i][j] |= (1 << 8);
            }
        }
        for (int j = 0; j < 5; j++)
        {
            for (int i = 34; i <= 139; i++)
            {
                pp[i][154 + j] |= (1 << 8);
            }
            for (int i = 99; i <= 204; i++)
            {
                pp[i][308 - j] |= (1 << 8);
            }
        }
        for (int i = 35; i <= 203; i++)
        {
            for (int j = 1; j <= 150; j++)
            {
                pp[i][j] |= (1 << 0);
            }
        }
    }
    if (situation == 7)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 1; j <= xk - 62; j++)
            {
                pp[34 - i][j] |= (1 << 8);
                if (j <= xk - 70) pp[204 + i][j] |= (1 << 8);
                if (j <= xk - 110)
                {
                    pp[116 + i][j] |= (1 << 8);
                }
            }
        }
        for (int i = 116; i <= 120; i++) {
            for (int j = xk - 4; j <= xk; j++) pp[i][j] |= (1 << 8);
        }
        int minus = 0, cnt = 0;
        for (int i = 116; i <= 203; i++)
        {
            for (int j = xk - 4 - minus; j <= xk - minus; j++) pp[i][j] |= (1 << 8);
            cnt++;
            if (cnt == 5)
            {
                minus += 4;
                cnt = 0;
            }
        }
        minus = 0, cnt = 0;
        for (int j = xk - 4; j <= xk; j++) pp[115][j] |= (1 << 8);
        for (int i = 114; i >= 35; i--)
        {
            for (int j = xk - 4 - minus; j <= xk - minus; j++) pp[i][j] |= (1 << 8);
            cnt++;
            if (cnt == 5)
            {
                minus += 4;
                cnt = 0;
            }
        }
        for (int i = 35; i <= 115; i++)
        {
            for (int j = 1; j <= 370; j++)
            {
                pp[i][j] |= (1 << 0);
            }
        }
    }
    if (situation == 8)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 1; j <= xk; j++)
            {
                pp[34 - i][j] |= (1 << 8);
                pp[204 + i][j] |= (1 << 8);
            }
        }
        for (int i = 90; i <= 150; i++)
        {
            for (int j = 220; j <= 260; j++)
            {
                pp[i][j] |= (1 << 8);
            }
        }
        for (int i = 90; i <= 150; i++) pp[i][219] |= (1 << 8);
        for (int i = 90; i <= 150; i++) pp[i][218] |= (1 << 8);
        for (int i = 88; i <= 152; i++) pp[i][217] |= (1 << 8);
        for (int i = 88; i <= 152; i++) pp[i][216] |= (1 << 8);
        for (int i = 88; i <= 152; i++) pp[i][215] |= (1 << 8);
        for (int i = 86; i <= 154; i++) pp[i][214] |= (1 << 8);
        for (int i = 86; i <= 154; i++) pp[i][213] |= (1 << 8);
        for (int i = 86; i <= 154; i++) pp[i][212] |= (1 << 8);
        for (int i = 86; i <= 154; i++) pp[i][211] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][210] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][209] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][208] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][207] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][206] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][205] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][204] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][203] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][202] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][201] |= (1 << 8);
        for (int i = 86; i <= 154; i++) pp[i][200] |= (1 << 8);
        for (int i = 86; i <= 154; i++) pp[i][199] |= (1 << 8);
        for (int i = 86; i <= 154; i++) pp[i][198] |= (1 << 8);
        for (int i = 86; i <= 154; i++) pp[i][197] |= (1 << 8);
        for (int i = 88; i <= 152; i++) pp[i][196] |= (1 << 8);
        for (int i = 88; i <= 152; i++) pp[i][195] |= (1 << 8);
        for (int i = 88; i <= 152; i++) pp[i][194] |= (1 << 8);
        for (int i = 90; i <= 150; i++) pp[i][193] |= (1 << 8);
        for (int i = 90; i <= 150; i++) pp[i][192] |= (1 << 8);
        for (int i = 92; i <= 148; i++) pp[i][191] |= (1 << 8);
        for (int i = 94; i <= 146; i++) pp[i][190] |= (1 << 8);
        for (int i = 98; i <= 142; i++) pp[i][189] |= (1 << 8);
        for (int i = 102; i <= 138; i++) pp[i][188] |= (1 << 8);
        for (int i = 107; i <= 133; i++) pp[i][187] |= (1 << 8);
        for (int i = 112; i <= 128; i++) pp[i][186] |= (1 << 8);
        for (int i = 35; i <= 203; i++)
        {
            for (int j = 1; j <= 150; j++)
            {
                pp[i][j] |= (1 << 0);
            }
        }
    }
    if (situation == 9)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 100; j <= xk - 100; j++)
            {
                pp[i + 15][j] |= (1 << 8);
                pp[yk - i - 15][j] |= (1 << 8);
            }
            for (int j = 0; j <= 103; j++)
            {
                pp[i + 85][j] |= (1 << 8);
                pp[yk - i - 85][j] |= (1 << 8);
            }
            for (int j = xk - 100; j <= xk; j++)
            {
                pp[i + 85][j] |= (1 << 8);
                pp[yk - i - 85][j] |= (1 << 8);
            }
        }
        for (int j = 0; j < 5; j++)
        {
            for (int i = 15; i <= 89; i++)
            {
                pp[i][j + 100] |= (1 << 8);
                pp[i][xk - 100 - j] |= (1 << 8);
            }
            for (int i = yk - 89; i <= yk - 15; i++)
            {
                pp[i][j + 100] |= (1 << 8);
                pp[i][xk - 100 - j] |= (1 << 8);
            }
        }
        for (int i = 90; i <= 150; i++)
        {
            for (int j = 200; j <= 260; j++)
            {
                pp[i][j] |= (1 << 8);
            }
        }
        for (int i = 90; i <= yk - 90; i++)
        {
            for (int j = 1; j <= 100; j++)
            {
                pp[i][j] |= (1 << 0);
            }
        }
    }
}

void Infinity(int xk, int yk, vector<vector<int>>& p, vector <vector<int>>& pp, int situation)
{
    if (situation == 2) for (int i = 6; i < 50; i++) pp[i][1] |= (1 << 0);
    if (situation == 3) for (int i = 35; i <= 115; i++) pp[i][1] |= (1 << 0);
    if (situation == 9) for (int i = 90; i <= yk - 90; i++) pp[i][1] |= (1 << 0);
    if (situation == 4 or situation == 6 or situation == 8) for (int i = 35; i <= 203; i++) pp[i][1] |= (1 << 0);
    if (situation == 5 or situation == 7) for (int i = 35; i <= 115; i++) pp[i][1] |= (1 << 0);
}

void Drawing(int xsize, int ysize, int xk, int yk, int cell, int r, vector<vector<int>>& p, bool lines, bool masscnt, int msum) {
    char variable[10];
    txSetFillColour(RGB(255, 255, 255));
    txClear();
    txSetFillColor(RGB(0, 0, 0));
    txSetColour(RGB(0, 0, 0));
    if (lines)
    {
        for (int i = 0; i < yk; i++) {
            txLine(0, i * cell, xsize, i * cell);
        }
        for (int i = 1; i < xk; i++) {
            txLine(i * cell, 0, i * cell, ysize);
        }
    }
    for (int i = 1; i <= yk; i++) {
        for (int j = 1; j <= xk; j++) {
            if (p[i][j] != 0) {
                if (p[i][j] == (1 << 8)) {
                    txRectangle(cell * (j - 1), cell * (i - 1), cell * j, cell * i);
                }
                else {
                    txCircle(r + (j - 1) * cell, r + (i - 1) * cell, r);
                }
            }
        }
    }
    if (masscnt)
    {
        txSelectFont("Times New Roman", 60);
        itoa(msum, variable, 10);
        txTextOut(50, 50, "Mass:");
        txTextOut(180, 50, variable);
    }
}

bool Mask(int p, int k) {
    if ((p & (1 << k)) != 0) return true;
    else return false;
}

void Change(int xk, int yk, vector<vector<int>>& p, vector<vector<int>>& pp) {
    for (int i = 0; i < yk + 2; i++) {
        for (int j = 0; j < xk + 2; j++) {
            p[i][j] = pp[i][j];
        }
    }
    for (int i = 0; i < yk + 2; i++) {
        for (int j = 0; j < xk + 2; j++) {
            if (pp[i][j] != (1 << 8)) {
                pp[i][j] = 0;
            }
        }
    }
}

void Stuck(int xk, int yk, vector<vector<int>>& p, vector<vector<int>>& pp) {
    for (int i = 1; i <= yk; i++) {
        for (int j = 1; j <= xk; j++) {
            if (Mask(p[i][j], 0) == true and (Mask(p[i][j + 1], 8) == true or j == xk)) {
                pp[i][j] |= (1 << 0);
            }
            if (Mask(p[i][j], 2) == true and (Mask(p[i - 1][j], 8) == true or i == 1)) {
                pp[i][j] |= (1 << 2);
            }
            if (Mask(p[i][j], 4) == true and (Mask(p[i][j - 1], 8) == true or j == 1)) {
                pp[i][j] |= (1 << 4);
            }
            if (Mask(p[i][j], 6) == true and (Mask(p[i + 1][j], 8) == true or i == yk)) {
                pp[i][j] |= (1 << 6);
            }
            if (Mask(p[i][j], 1) == true) {
                if (i == 1 or j == xk) pp[i][j] |= (1 << 1);
                else if (Mask(p[i][j + 1], 8) == true or Mask(p[i - 1][j], 8) == true) pp[i][j] |= (1 << 1);
                else if (Mask(p[i][j + 1], 8) == false and Mask(p[i - 1][j], 8) == false and
                    Mask(p[i - 1][j + 1], 8) == true) pp[i][j] |= (1 << 1);
            }
            if (Mask(p[i][j], 3) == true) {
                if (i == 1 or j == 1) pp[i][j] |= (1 << 3);
                else if (Mask(p[i][j - 1], 8) == true or Mask(p[i - 1][j], 8) == true) pp[i][j] |= (1 << 3);
                else if (Mask(p[i][j - 1], 8) == false and Mask(p[i - 1][j], 8) == false and
                    Mask(p[i - 1][j - 1], 8) == true) pp[i][j] |= (1 << 3);
            }
            if (Mask(p[i][j], 5) == true) {
                if (i == yk or j == 1) pp[i][j] |= (1 << 5);
                else if (Mask(p[i][j - 1], 8) == true or Mask(p[i + 1][j], 8) == true) pp[i][j] |= (1 << 5);
                else if (Mask(p[i][j - 1], 8) == false and Mask(p[i + 1][j], 8) == false and
                    Mask(p[i + 1][j - 1], 8) == true) pp[i][j] |= (1 << 5);
            }
            if (Mask(p[i][j], 7) == true) {
                if (i == yk or j == xk) pp[i][j] |= (1 << 7);
                else if (Mask(p[i][j + 1], 8) == true or Mask(p[i + 1][j], 8) == true) pp[i][j] |= (1 << 7);
                else if (Mask(p[i][j + 1], 8) == false and Mask(p[i + 1][j], 8) == false and
                    Mask(p[i + 1][j + 1], 8) == true) pp[i][j] |= (1 << 7);
            }
        }
    }
}

void Rotation180(int &k) {
    k = (k + 4) % 8;
}

void Rotation90(int& k) {
    k = (k + 2) % 8;
}

void Rotation270(int& k) {
    k = (k + 6) % 8;
}

void Move(int xk, int yk, vector<vector<int>>& p, vector<vector<int>>& pp) {
    for (int i = 1; i <= yk; i++) {
        for (int j = 1; j <= xk; j++) {
            if (p[i][j] != (1 << 8)) {
                if (Mask(p[i][j - 1], 0) == true) {
                    pp[i][j] |= (1 << 0);
                }
                if (Mask(p[i + 1][j - 1], 1) == true) {
                    pp[i][j] |= (1 << 1);
                }
                if (Mask(p[i + 1][j], 2) == true) {
                    pp[i][j] |= (1 << 2);
                }
                if (Mask(p[i + 1][j + 1], 3) == true) {
                    pp[i][j] |= (1 << 3);
                }
                if (Mask(p[i][j + 1], 4) == true) {
                    pp[i][j] |= (1 << 4);
                }
                if (Mask(p[i - 1][j + 1], 5) == true) {
                    pp[i][j] |= (1 << 5);
                }
                if (Mask(p[i - 1][j], 6) == true) {
                    pp[i][j] |= (1 << 6);
                }
                if (Mask(p[i - 1][j - 1], 7) == true) {
                    pp[i][j] |= (1 << 7);
                }
            }
        }
    }
}

void Rebound(int xk, int yk, vector<vector<int>>& p, vector<vector<int>>& pp, bool borders, int &k) {
    if (borders)
    {
        for (int i = 1; i <= xk; i++) {
            if (Mask(pp[1][i], 1) == true) {
                k = 1;
                pp[1][i] &= ~(1 << k);
                Rotation270(k);
                pp[1][i] |= (1 << k);
            }
            if (Mask(pp[1][i], 2) == true) {
                k = 2;
                pp[1][i] &= ~(1 << k);
                Rotation180(k);
                pp[1][i] |= (1 << k);
            }
            if (Mask(pp[1][i], 3) == true) {
                k = 3;
                pp[1][i] &= ~(1 << k);
                Rotation90(k);
                pp[1][i] |= (1 << k);
            }
            if (Mask(pp[yk][i], 5) == true) {
                k = 5;
                pp[yk][i] &= ~(1 << k);
                Rotation270(k);
                pp[yk][i] |= (1 << k);
            }
            if (Mask(pp[yk][i], 6) == true) {
                k = 6;
                pp[yk][i] &= ~(1 << k);
                Rotation180(k);
                pp[yk][i] |= (1 << k);
            }
            if (Mask(pp[yk][i], 7) == true) {
                k = 7;
                pp[yk][i] &= ~(1 << k);
                Rotation90(k);
                pp[yk][i] |= (1 << k);
            }
        }
        for (int i = 1; i <= yk; i++) {
            if (Mask(pp[i][1], 3) == true) {
                k = 3;
                pp[i][1] &= ~(1 << k);
                Rotation270(k);
                pp[i][1] |= (1 << k);
            }
            if (Mask(pp[i][1], 4) == true) {
                k = 4;
                pp[i][1] &= ~(1 << k);
                Rotation180(k);
                pp[i][1] |= (1 << k);
            }
            if (Mask(pp[i][1], 5) == true) {
                k = 5;
                pp[i][1] &= ~(1 << k);
                Rotation90(k);
                pp[i][1] |= (1 << k);
            }
            if (Mask(pp[i][xk], 7) == true) {
                k = 7;
                pp[i][xk] &= ~(1 << k);
                Rotation270(k);
                pp[i][xk] |= (1 << k);
            }
            if (Mask(pp[i][xk], 0) == true) {
                k = 0;
                pp[i][xk] &= ~(1 << k);
                Rotation180(k);
                pp[i][xk] |= (1 << k);
            }
            if (Mask(pp[i][xk], 1) == true) {
                k = 1;
                pp[i][xk] &= ~(1 << k);
                Rotation90(k);
                pp[i][xk] |= (1 << k);
            }
        }
    }
    for (int i = 1; i <= yk; i++) {
        for (int j = 1; j <= xk; j++) {
            if (Mask(pp[i][j], 0) == true and Mask(pp[i][j + 1], 8) == true) {
                k = 0;
                pp[i][j] &= ~(1 << k);
                Rotation180(k);
                pp[i][j] |= (1 << k);
            }
            if (Mask(pp[i][j], 2) == true and Mask(pp[i - 1][j], 8) == true) {
                k = 2;
                pp[i][j] &= ~(1 << k);
                Rotation180(k);
                pp[i][j] |= (1 << k);
            }
            if (Mask(pp[i][j], 4) == true and Mask(pp[i][j - 1], 8) == true) {
                k = 4;
                pp[i][j] &= ~(1 << k);
                Rotation180(k);
                pp[i][j] |= (1 << k);
            }
            if (Mask(pp[i][j], 6) == true and Mask(pp[i + 1][j], 8) == true) {
                k = 6;
                pp[i][j] &= ~(1 << k);
                Rotation180(k);
                pp[i][j] |= (1 << k);
            }
            if (Mask(pp[i][j], 1) == true) {
                if (pp[i][j + 1] == (1 << 8)) {
                    k = 1;
                    pp[i][j] &= ~(1 << k);
                    Rotation90(k);
                    pp[i][j] |= (1 << k);
                }
                else if (pp[i - 1][j] == (1 << 8)) {
                    k = 1;
                    pp[i][j] &= ~(1 << k);
                    Rotation270(k);
                    pp[i][j] |= (1 << k);
                }
                else if (pp[i][j + 1] != (1 << 8) and pp[i - 1][j] != (1 << 8) and
                    pp[i - 1][j + 1] == (1 << 8)) {
                    k = 1;
                    pp[i][j] &= ~(1 << k);
                    Rotation180(k);
                    pp[i][j] |= (1 << k);
                }
            }
            if (Mask(pp[i][j], 3) == true) {
                if (pp[i - 1][j] == (1 << 8)) {
                    k = 3;
                    pp[i][j] &= ~(1 << k);
                    Rotation90(k);
                    pp[i][j] |= (1 << k);
                }
                else if (pp[i][j - 1] == (1 << 8)) {
                    k = 3;
                    pp[i][j] &= ~(1 << k);
                    Rotation270(k);
                    pp[i][j] |= (1 << k);
                }
                else if (pp[i][j - 1] != (1 << 8) and pp[i - 1][j] != (1 << 8) and
                    pp[i - 1][j - 1] == (1 << 8)) {
                    k = 3;
                    pp[i][j] &= ~(1 << k);
                    Rotation180(k);
                    pp[i][j] |= (1 << k);
                }
            }
            if (Mask(pp[i][j], 5) == true) {
                if (pp[i][j - 1] == (1 << 8)) {
                    k = 5;
                    pp[i][j] &= ~(1 << k);
                    Rotation90(k);
                    pp[i][j] |= (1 << k);
                }
                else if (pp[i + 1][j] == (1 << 8)) {
                    k = 5;
                    pp[i][j] &= ~(1 << k);
                    Rotation270(k);
                    pp[i][j] |= (1 << k);
                }
                else if (pp[i][j - 1] != (1 << 8) and pp[i + 1][j] != (1 << 8) and
                    pp[i + 1][j - 1] == (1 << 8)) {
                    k = 5;
                    pp[i][j] &= ~(1 << k);
                    Rotation180(k);
                    pp[i][j] |= (1 << k);
                }
            }
            if (Mask(pp[i][j], 7) == true) {
                if (pp[i + 1][j] == (1 << 8)) {
                    k = 7;
                    pp[i][j] &= ~(1 << k);
                    Rotation90(k);
                    pp[i][j] |= (1 << k);
                }
                else if (pp[i][j + 1] == (1 << 8)) {
                    k = 7;
                    pp[i][j] &= ~(1 << k);
                    Rotation270(k);
                    pp[i][j] |= (1 << k);
                }
                else if (pp[i][j + 1] != (1 << 8) and pp[i + 1][j] != (1 << 8) and
                    pp[i + 1][j + 1] == (1 << 8)) {
                    k = 7;
                    pp[i][j] &= ~(1 << k);
                    Rotation180(k);
                    pp[i][j] |= (1 << k);
                }
            }
            if (Mask(pp[i][j], 1) == true) {
                if (pp[i][j + 1] == (1 << 8)) {
                    k = 1;
                    pp[i][j] &= ~(1 << k);
                    Rotation90(k);
                    pp[i][j] |= (1 << k);
                }
                else if (pp[i - 1][j] == (1 << 8)) {
                    k = 1;
                    pp[i][j] &= ~(1 << k);
                    Rotation270(k);
                    pp[i][j] |= (1 << k);
                }
                else if (pp[i][j + 1] != (1 << 8) and pp[i - 1][j] != (1 << 8) and
                    pp[i - 1][j + 1] == (1 << 8)) {
                    k = 1;
                    pp[i][j] &= ~(1 << k);
                    Rotation180(k);
                    pp[i][j] |= (1 << k);
                }
            }
        }
    }
}

void Collision(int xk, int yk, vector<vector<int>>& p, vector<vector<int>>& pp,
    vector<int> xspeed, vector<int> yspeed, bool abscollision) {
    int ppsub, gsub;
    int ppmass, gmass;
    int ppximpulse, ppyimpulse, gximpulse, gyimpulse;
    int ppcount, gcount;
    int choices[256], chcount;
    int check;
    for (int i = 1; i <= yk; i++) {
        for (int j = 1; j <= xk; j++) {
            ppsub = pp[i][j];
            if (Mask(ppsub, 8)) continue;
            ppmass = 0;
            ppximpulse = 0;
            ppyimpulse = 0;
            ppcount = 0;
            while (ppsub != 0) {
                if (ppsub % 2 == 1) {
                    ppmass++;
                    ppximpulse += xspeed[ppcount];
                    ppyimpulse += yspeed[ppcount];
                }
                ppsub /= 2;
                ppcount++;
            }
            if (ppmass > 1) {
                for (int h = 0; h < 256; h++) {
                    choices[h] = 0;
                }
                chcount = 0;
                for (int g = 1; g < 256; g++) {
                    gsub = g;
                    gmass = 0;
                    gximpulse = 0;
                    gyimpulse = 0;
                    gcount = 0;
                    while (gsub != 0) {
                        if (gsub % 2 == 1) {
                            gmass++;
                            gximpulse += xspeed[gcount];
                            gyimpulse += yspeed[gcount];
                        }
                        gsub /= 2;
                        gcount++;
                    }
                    if (g != pp[i][j] and ppmass == gmass)
                    {
                        if ((abscollision and abs(ppximpulse) == abs(gximpulse) and abs(ppyimpulse) == abs(gyimpulse)) or
                            (abscollision == 0 and ppximpulse == gximpulse and ppyimpulse == gyimpulse)) {
                            check = 1;
                            if ((Mask(g, 2) and Mask(g, 6) == true) and
                                (Mask(p[i + 1][j], 8) or Mask(p[i - 1][j], 8) == true)) check = 0;
                            if ((Mask(g, 1) and Mask(g, 7) == true) and
                                (Mask(p[i + 1][j], 8) or Mask(p[i - 1][j], 8) == true)) check = 0;
                            if ((Mask(g, 3) and Mask(g, 5) == true) and
                                (Mask(p[i + 1][j], 8) or Mask(p[i - 1][j], 8) == true)) check = 0;
                            if ((Mask(g, 0) and Mask(g, 4) == true) and
                                (Mask(p[i][j + 1], 8) or Mask(p[i][j - 1], 8) == true)) check = 0;
                            if ((Mask(g, 5) and Mask(g, 7) == true) and
                                (Mask(p[i][j + 1], 8) or Mask(p[i][j - 1], 8) == true)) check = 0;
                            if ((Mask(g, 1) and Mask(g, 3) == true) and
                                (Mask(p[i][j + 1], 8) or Mask(p[i][j - 1], 8) == true)) check = 0;
                            if (Mask(g, 1) and Mask(g, 5) == true) {
                                if (p[i][j + 1] != (1 << 8) and p[i - 1][j] != (1 << 8) and
                                    p[i - 1][j + 1] == (1 << 8)) check = 0;
                                else if (p[i][j + 1] == (1 << 8) and p[i - 1][j] == (1 << 8)) check = 0;
                                else if (p[i][j - 1] != (1 << 8) and p[i + 1][j] != (1 << 8) and
                                    p[i + 1][j - 1] == (1 << 8)) check = 0;
                                else if (p[i][j - 1] == (1 << 8) and p[i + 1][j] == (1 << 8)) check = 0;
                            }
                            if (Mask(g, 3) and Mask(g, 7) == true) {
                                if (p[i][j - 1] != (1 << 8) and p[i - 1][j] != (1 << 8) and
                                    p[i - 1][j - 1] == (1 << 8)) check = 0;
                                else if (p[i][j - 1] == (1 << 8) and p[i - 1][j] == (1 << 8)) check = 0;
                                else if (p[i][j + 1] != (1 << 8) and p[i + 1][j] != (1 << 8) and
                                    p[i + 1][j + 1] == (1 << 8)) check = 0;
                                else if (p[i][j + 1] == (1 << 8) and p[i + 1][j] == (1 << 8)) check = 0;
                            }
                            if (check == 1) {
                                if (i != 1 and j != 1 and i != yk and j != xk) {
                                    choices[chcount] = g;
                                    chcount++;
                                }
                                if (i == 1 or i == yk) {
                                    if ((Mask(g, 2) and Mask(g, 6) == false) and
                                        (Mask(g, 1) and Mask(g, 7) == false) and
                                        (Mask(g, 3) and Mask(g, 5) == false)) {
                                        choices[chcount] = g;
                                        chcount++;
                                    }
                                }
                                if (j == 1 or j == yk) {
                                    if ((Mask(g, 0) and Mask(g, 4) == false) and
                                        (Mask(g, 5) and Mask(g, 7) == false) and
                                        (Mask(g, 1) and Mask(g, 3) == false)) {
                                        choices[chcount] = g;
                                        chcount++;
                                    }
                                }
                            }
                        }
                    }
                }
                if (chcount != 0) {
                    pp[i][j] = choices[rand() % chcount];
                }
            }
        }
    }
}

void MassCount(int &msum, int xk, int yk, vector<vector<int>>& p) {
    msum = 0;
    for (int i = 0; i < yk + 2; i++) {
        for (int j = 0; j < xk + 2; j++) {
            if (Mask(p[i][j], 0) == true) msum++;
            if (Mask(p[i][j], 1) == true) msum++;
            if (Mask(p[i][j], 2) == true) msum++;
            if (Mask(p[i][j], 3) == true) msum++;
            if (Mask(p[i][j], 4) == true) msum++;
            if (Mask(p[i][j], 5) == true) msum++;
            if (Mask(p[i][j], 6) == true) msum++;
            if (Mask(p[i][j], 7) == true) msum++;
        }
    }
}

int main()
{
    srand(time(0));

    int
        xsize = 1850,
        ysize = 950,
        cell = 4,
        procent = 20,
        sleeptime = 5,
        situation = 9;
    bool
        lines = 0,
        masscnt = 0,
        abscollision = 0,
        borders = 0,
        infinity = 1,
        readfile = 1;

    if (readfile) {
        ifstream fin;
        fin.open("Parameters.txt");
        int z = 1;
        if (!fin.is_open())
        {
            cout << "ERROR!!!\n";
            return 0;
        }
        else {
            while (1) {
                string sub; fin >> sub;
                if (isdigit(sub[0]))
                {
                    if (z == 1) procent = stoi(sub);
                    if (z == 2) sleeptime = stoi(sub);
                    if (z == 3) situation = stoi(sub);
                    if (z == 4) lines = (bool)stoi(sub);
                    if (z == 5) masscnt = (bool)stoi(sub);
                    if (z == 6) abscollision = (bool)stoi(sub);
                    if (z == 7) borders = (bool)stoi(sub);
                    if (z == 8) infinity = (bool)stoi(sub);
                    z++;
                }
                if (z == 9) break;
            }
        }
        fin.close();
    }

    int
        xk = xsize / cell,
        yk = ysize / cell,
        msum = 0, k = 0;
    vector<vector<int>> p(yk + 2, vector<int>(xk + 2));
    vector<vector<int>> pp(yk + 2, vector<int>(xk + 2));
    vector<int> xspeed = {1, 1, 0, -1, -1, -1, 0, 1};
    vector<int> yspeed = { 0, -1, -1, -1, 0, 1, 1, 1 };
    float r = cell / 2.0;

    Initialization(xk, yk, p, pp, situation, procent);
    Rebound(xk, yk, p, pp, borders, k);
    Change(xk, yk, p, pp);
    txCreateWindow(xsize, ysize);
    while (!_kbhit()) {
        if (infinity) Infinity(xk, yk, p, pp, situation);
        MassCount(msum, xk, yk, p);
        Drawing(xsize, ysize, xk, yk, cell, r, p, lines, masscnt, msum);
        Move(xk, yk, p, pp);
        Collision(xk, yk, p, pp, xspeed, yspeed, abscollision);
        Rebound(xk, yk, p, pp,  borders, k);
        if (borders) Stuck(xk, yk, p, pp);
        Change(xk, yk, p, pp);
        Sleep(sleeptime);
    }
}
