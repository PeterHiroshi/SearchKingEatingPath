//
//  Header.h
//  SearchKingEatingPath
//
//  Created by 清水ヒロシ on 2018/07/19.
//  Copyright © 2018年 ice-stone. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <vector>

using namespace std;

// global varibles
const int BOARDTYPE = 10;

//const int CHESSBOARD[BOARDTYPE][BOARDTYPE] = {
//    {-3,0,-3,0,-3,0,-3,0,-3,0},
//    {0,-3,0,-3,0,-3,0,-3,0,-3},
//    {-3,0,-3,0,-3,0,-3,0,-3,0},
//    {0,-3,0,-3,0,-3,0,-3,0,-3},
//    {-3,0,-3,0,-3,0,-3,0,-3,0},
//    {0,-3,0,-3,0,-3,0,-3,0,-3},
//    {-3,0,-3,0,-3,0,-3,0,-3,0},
//    {0,-3,0,-3,0,-3,0,-3,0,-3},
//    {-3,0,-3,0,-3,0,-3,0,-3,0},
//    {0,-3,0,-3,0,-3,0,-3,0,-3}};

//// (8,1)->[(3,6)->(0,3)->(3,0)]->(5,2)
//const int CHESSBOARD[BOARDTYPE][BOARDTYPE] = {
//    {-3,0,-3,0,-3,0,-3,0,-3,0},
//    {0,-3,1,-3,0,-3,0,-3,0,-3},
//    {-3,0,-3,0,-3,1,-3,0,-3,0},
//    {0,-3,0,-3,0,-3,0,-3,0,-3},
//    {-3,1,-3,0,-3,0,-3,0,-3,0},
//    {0,-3,0,-3,1,-3,0,-3,0,-3},
//    {-3,0,-3,0,-3,0,-3,0,-3,0},
//    {0,-3,0,-3,0,-3,0,-3,0,-3},
//    {-3,-2,-3,0,-3,0,-3,0,-3,0},
//    {0,-3,0,-3,0,-3,0,-3,0,-3}};

// (8,1)->[(3,6)->(0,3)->(3,0)
const int CHESSBOARD[BOARDTYPE][BOARDTYPE] = {
    {-3,0,-3,0,-3,0,-3,0,-3,0},
    {0,-3,1,-3,0,-3,0,-3,0,-3},
    {-3,0,-3,0,-3,1,-3,0,-3,0},
    {0,-3,0,-3,0,-3,0,-3,0,-3},
    {-3,0,-3,0,-3,0,-3,0,-3,0},
    {0,-3,1,-3,1,-3,0,-3,0,-3},
    {-3,0,-3,0,-3,0,-3,0,-3,0},
    {0,-3,0,-3,0,-3,0,-3,0,-3},
    {-3,-2,-3,0,-3,0,-3,0,-3,0},
    {0,-3,0,-3,0,-3,0,-3,0,-3}};

// structs
struct PiecePos
{
    int row;
    int col;
    PiecePos(int row, int col) :
        row(row), col(col)
    {}
    
};

// functions
std::vector<PiecePos> getMiddleEatedPoses(const PiecePos& begin_pos, const PiecePos& end_pos,
                                          const vector<PiecePos>& eat_lst,
                                          const int chessboard[BOARDTYPE][BOARDTYPE]);
std::vector<PiecePos> getCandidatePoses(const PiecePos& end_pos, const vector<PiecePos>& eat_lst,
                                        const int chessboard[BOARDTYPE][BOARDTYPE]);
std::vector<PiecePos> find_road(PiecePos ppos, int dir_row, int dir_col,
                                const int chessboard[BOARDTYPE][BOARDTYPE]);

std::vector<PiecePos> find_intersections(const vector<PiecePos>& lst1, const vector<PiecePos>& lst2);

bool searchEatingPath(PiecePos cur_pos, const PiecePos& end_pos, const vector<PiecePos>& eat_lst,
                      bool visited[], const vector<PiecePos>& candi_poses, vector<PiecePos>& mid_poses);


#endif /* Header_h */
