#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

// Function to apply a permutation to a list
std::vector<int> perm_apply(const std::vector<int>& perm, const std::vector<int>& position) {
    std::vector<int> result(position.size());
    for (int i = 0; i < position.size(); ++i) {
        result[i] = position[perm[i]];
    }
    return result;
}

// Function to find the inverse of a permutation
std::vector<int> perm_inverse(const std::vector<int>& p) {
    int n = p.size();
    std::vector<int> q(n);
    for (int i = 0; i < n; ++i) {
        q[p[i]] = i;
    }
    return q;
}

// Function to convert a permutation to a string
std::string perm_to_string(const std::vector<int>& p) {
    std::string s = "(";
    for (int x : p) {
        s += " " + std::to_string(x);
    }
    s += " )";
    return s;
}

std::vector<int> input_configuration() {
    std::vector<int> position(24, -1);
    std::string cubie;

    std::cout << "Look for the cubie with yellow, blue, and orange faces (it has the Rubiks mark). Put this cubie in the lower-back-right corner with the yellow face down. We will call this cubie #7.\n";

    std::cout << "Now look at the cubie in the upper-front-left corner. We will call this cubie #0. Starting with its front face, and going clockwise, input the colors of the faces (e.g. yob, if the colors are yellow, orange, and blue):\n";
    std::cout << "cubie #0: ";
    std::cin >> cubie;
    position[0] = std::stoi(cubie);
    position[1] = std::stoi(cubie.substr(1) + cubie[0]);
    position[2] = std::stoi(cubie.substr(2) + cubie.substr(0, 2));

    std::cout << "Now enter cubie #1, which is to the right of cubie #0, again starting with the front face and going clockwise:\n";
    std::cout << "cubie #1: ";
    std::cin >> cubie;
    position[3] = std::stoi(cubie);
    position[4] = std::stoi(cubie.substr(1) + cubie[0]);
    position[5] = std::stoi(cubie.substr(2) + cubie.substr(0, 2));

    std::cout << "Now enter cubie #2, which is beneath cubie #0:\n";
    std::cout << "cubie #2: ";
    std::cin >> cubie;
    position[6] = std::stoi(cubie);
    position[7] = std::stoi(cubie.substr(1) + cubie[0]);
    position[8] = std::stoi(cubie.substr(2) + cubie.substr(0, 2));

    std::cout << "Now enter cubie #3, to the right of cubie #2:\n";
    std::cout << "cubie #3: ";
    std::cin >> cubie;
    position[9] = std::stoi(cubie);
    position[10] = std::stoi(cubie.substr(1) + cubie[0]);
    position[11] = std::stoi(cubie.substr(2) + cubie.substr(0, 2));

    std::cout << "Now enter cubie #4, which is behind cubie #0. Start with the back face, and go clockwise:\n";
    std::cout << "cubie #4: ";
    std::cin >> cubie;
    position[12] = std::stoi(cubie);
    position[13] = std::stoi(cubie.substr(1) + cubie[0]);
    position[14] = std::stoi(cubie.substr(2) + cubie.substr(0, 2));

    std::cout << "Now enter cubie #5, which is to the right of cubie #4:\n";
    std::cout << "cubie #5: ";
    std::cin >> cubie;
    position[15] = std::stoi(cubie);
    position[16] = std::stoi(cubie.substr(1) + cubie[0]);
    position[17] = std::stoi(cubie.substr(2) + cubie.substr(0, 2));

    std::cout << "Now enter cubie #6, which is beneath cubie #4:\n";
    std::cout << "cubie #6: ";
    std::cin >> cubie;
    position[18] = std::stoi(cubie);
    position[19] = std::stoi(cubie.substr(1) + cubie[0]);
    position[20] = std::stoi(cubie.substr(2) + cubie.substr(0, 2));

    std::cout << "We already know cubie #7, so we're done.\n";
    cubie = "oyb";
    position[21] = std::stoi(cubie);
    position[22] = std::stoi(cubie.substr(1) + cubie[0]);
    position[23] = std::stoi(cubie.substr(2) + cubie.substr(0, 2));

    return position;
}


int main()
{
    int rgw, flu, gwr, luf, wrg, ufl, rwb, fur, wbr, urf, brw, rfu, ryg, fdl, ygr, dlf, gry, lfd, rby, frd, byr, rdf, yrb, dfr, owg, bul, wgo, ulb, gow, lbu, obw, bru, bwo, rub, wob, ubr, ogy, bld, gyo, ldb, yog, dbl, oyb, bdr, ybo, drb, boy, rbd;
    
    rgw = flu = 0; // 0-th cubie; front face
    gwr = luf = 1; // 0-th cubie; left face
    wrg = ufl = 2; // 0-th cubie; up face

    rwb = fur = 3; // 1-st cubie; front face
    wbr = urf = 4; // 1-st cubie; up face
    brw = rfu = 5; // 1-st cubie; right face

    ryg = fdl = 6; // 2-nd cubie; front face
    ygr = dlf = 7; // 2-nd cubie; down face
    gry = lfd = 8; // 2-nd cubie; left face

    rby = frd = 9; // 3-rd cubie; front face
    byr = rdf = 10; // 3-rd cubie; right face
    yrb = dfr = 11; // 3-rd cubie; down face

    owg = bul = 12; // 4-th cubie; back face
    wgo = ulb = 13; // 4-th cubie; up face
    gow = lbu = 14; // 4-th cubie; left face

    obw = bru = 15; // 5-th cubie; back face
    bwo = rub = 16; // 5-th cubie; right face
    wob = ubr = 17; // 5-th cubie; up face

    ogy = bld = 18; // 6-th cubie; back face
    gyo = ldb = 19; // 6-th cubie; left face
    yog = dbl = 20; // 6-th cubie; down face

    oyb = bdr = 21; // 7-th cubie; back face
    ybo = drb = 22; // 7-th cubie; down face
    boy = rbd = 23; // 7-th cubie; right face

    std::vector<int> I = {flu, luf, ufl, fur, urf, rfu, fdl, dlf, lfd, frd, rdf, dfr, bul, ulb, lbu, bru, rub, ubr, bld, ldb, dbl, bdr, drb, rbd};

    std::vector<int> F = {fdl, dlf, lfd, flu, luf, ufl, frd, rdf, dfr, fur, urf, rfu, bul, ulb, lbu, bru, rub, ubr, bld, ldb, dbl, bdr, drb, rbd};
    // Front face rotated counter-clockwise.
    std::vector<int> Fi = perm_inverse(F);

    std::vector<int> L = {ulb, lbu, bul, fur, urf, rfu, ufl, flu, luf, frd, rdf, dfr, dbl, bld, ldb, bru, rub, ubr, dlf, lfd, fdl, bdr, drb, rbd};
    // Left face rotated clockwise.
    std::vector<int> Li = perm_inverse(L);

    std::vector<int> U = {rfu, fur, urf, rub, ubr, bru, fdl, dlf, lfd, frd, rdf, dfr, luf, ufl, flu, lbu, bul, ulb, bld, ldb, dbl, bdr, drb, rbd};
    // Upper face rotated clockwise.
    std::vector<int> Ui = perm_inverse(U);

    std::vector<std::vector<int>> quarter_twists = {F, Fi, L, Li, U, Ui};
    std::unordered_map<std::vector<int>, std::string> quarter_twists_names = {{F, "F"}, {Fi, "Fi"}, {L, "L"}, {Li, "Li"}, {U, "U"}, {Ui, "Ui"}};

    return 0;

}
