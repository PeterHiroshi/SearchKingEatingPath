//
//  main.cpp
//  SearchKingEatingPath
//
//  Created by 清水ヒロシ on 2018/07/19.
//  Copyright © 2018年 ice-stone. All rights reserved.
//

#include "Header.h"

std::vector<PiecePos> getMiddleEatedPoses(const PiecePos& begin_pos, const PiecePos& end_pos,
                                          const vector<PiecePos>& eat_lst, const int chessboard[10][10])
{
    vector<PiecePos> mid_poses;
    bool* visited = new bool[eat_lst.size()];
    for (int i=0; i<eat_lst.size(); ++i)
        visited[i] = false;
    vector<PiecePos> candi_poses = getCandidatePoses(end_pos, eat_lst, chessboard);
    
    if (searchEatingPath(begin_pos, end_pos, eat_lst, visited, candi_poses, mid_poses))
        mid_poses.pop_back();
    
    if (visited)
        delete[] visited;
    
    return mid_poses;
}

bool searchEatingPath(PiecePos cur_pos, const PiecePos& end_pos, const vector<PiecePos>& eat_lst,
                      bool visited[], const vector<PiecePos>& candi_poses, vector<PiecePos>& mid_poses)
{
    if ((cur_pos.row == end_pos.row) &&
        (cur_pos.col == end_pos.col)) {
        int i = 0;
        for (; i<eat_lst.size(); ++i) {
            if (visited[i] == false)
                break;
        }
        if (i == eat_lst.size())
            return true;
    }
    
    for (int i=0; i<eat_lst.size(); ++i) {
        if (!visited[i]) {
            
            int offset_row_cur_eat = eat_lst.at(i).row - cur_pos.row;
            int offset_col_cur_eat = eat_lst.at(i).col - cur_pos.col;
            
            // check if at the same diagonal line
            if (std::abs(offset_row_cur_eat) == std::abs(offset_col_cur_eat)) {
                int dir_row_cur_eat = offset_row_cur_eat / std::abs(offset_row_cur_eat);
                int dir_col_cur_eat = offset_col_cur_eat / std::abs(offset_col_cur_eat);
                
                for (vector<PiecePos>::const_iterator iter = candi_poses.begin();
                     iter != candi_poses.end(); ++iter) {
                    int offset_row_cur_candi = iter->row - cur_pos.row;
                    int offset_col_cur_candi = iter->col - cur_pos.col;
                    
                    // check if at the same diagonal line
                    if ((offset_row_cur_candi != 0) &&
                        (offset_col_cur_candi != 0) &&
                        std::abs(offset_row_cur_candi) == std::abs(offset_col_cur_candi)) {
                        int dir_row_cur_candi = offset_row_cur_candi / std::abs(offset_row_cur_candi);
                        int dir_col_cur_candi = offset_col_cur_candi / std::abs(offset_col_cur_candi);
                        
                        if ((dir_row_cur_eat == dir_row_cur_candi) &&
                            (dir_col_cur_eat == dir_col_cur_candi) &&
                            (std::abs(offset_row_cur_eat) < std::abs(offset_row_cur_candi)) &&
                            (std::abs(offset_col_cur_eat) < std::abs(offset_col_cur_candi))) {
                            
                            visited[i] = true;
                            mid_poses.push_back(*iter);
                            
                            if (searchEatingPath(*iter, end_pos, eat_lst, visited, candi_poses, mid_poses))
                                return true;
                            
                            visited[i] = false;
                            mid_poses.pop_back();
                            
                            
                        }
                    }
                
                }
            }
            
        }
    }
    
    return false;
    
}

std::vector<PiecePos> getCandidatePoses(const PiecePos& end_pos, const vector<PiecePos>& eat_lst,
                                        const int chessboard[10][10])
{
    vector<PiecePos> candi_poses;
    
    vector<PiecePos> dir4_roads_poses;
    
    vector<vector<PiecePos>> all_roads;
    
    for (int i=0; i<eat_lst.size(); ++i) {
        // 4 directions
        
        for (int dir_row = -1; dir_row <= 1; dir_row += 2) {
            for (int dir_col = -1; dir_col <= 1; dir_col += 2) {
                vector<PiecePos> dir_road_poses = find_road(eat_lst[i], dir_row, dir_col, chessboard);
                
                for (int j=0; j<dir_road_poses.size(); ++j) {
                    dir4_roads_poses.push_back(dir_road_poses[j]);
                }
                
            }
        }
        
        all_roads.push_back(dir4_roads_poses);
        dir4_roads_poses.clear();
        
    }

    for (int i=0; i<all_roads.size(); ++i) {
        for (int j=i+1; j<all_roads.size(); ++j) {
            vector<PiecePos> inters = find_intersections(all_roads.at(i), all_roads.at(j));
            for (vector<PiecePos>::const_iterator iter = inters.begin();
                 iter != inters.end(); ++iter) {
                candi_poses.push_back(*iter);
            }
        }
    }
    
    candi_poses.push_back(end_pos);
    
    return candi_poses;
}

std::vector<PiecePos> find_road(PiecePos ppos, int dir_row, int dir_col,
                                const int chessboard[BOARDTYPE][BOARDTYPE])
{
    vector<PiecePos> poses_in_road;
    
    PiecePos neighbor = PiecePos(ppos.row+dir_row, ppos.col+dir_col);
    for (int i=0; i<BOARDTYPE; ++i) {
        if ((neighbor.row >= 0 && neighbor.row < BOARDTYPE) &&
            (neighbor.col >= 0 && neighbor.col < BOARDTYPE) &&
            (chessboard[neighbor.row][neighbor.col] == 0)) {
            poses_in_road.push_back(neighbor);
        }
        else
            break;
        
        neighbor.row += dir_row;
        neighbor.col += dir_col;
    }
    
    return poses_in_road;
}

std::vector<PiecePos> find_intersections(const vector<PiecePos>& lst1,
                                        const vector<PiecePos>& lst2)
{
    vector<PiecePos> inters;
    for (int i=0; i<lst1.size(); ++i) {
        for (int j=0; j<lst2.size(); ++j) {
            if ((lst1.at(i).row == lst2.at(j).row) &&
                (lst1.at(i).col == lst2.at(j).col))
                inters.push_back(lst1.at(i));
        }
    }
    
    return inters;
    
}

int main(int argc, const char * argv[]) {
    
    PiecePos eat1 = PiecePos(1, 2);
    PiecePos eat2 = PiecePos(2, 5);
//    PiecePos eat3 = PiecePos(4, 1);
    PiecePos eat3 = PiecePos(5, 2);
    PiecePos eat4 = PiecePos(5, 4);
    vector<PiecePos> eat_lst;
    eat_lst.push_back(eat1);
    eat_lst.push_back(eat2);
    eat_lst.push_back(eat3);
    eat_lst.push_back(eat4);
//    vector<PiecePos> mid_poses = getMiddleEatedPoses(PiecePos(8,1), PiecePos(5,2), eat_lst, CHESSBOARD);
    vector<PiecePos> mid_poses = getMiddleEatedPoses(PiecePos(8,1), PiecePos(6,3), eat_lst, CHESSBOARD);
    for (vector<PiecePos>::const_iterator iter = mid_poses.begin();
         iter != mid_poses.end(); ++iter) {
        cout << "(" << iter->row << "," << iter->col << ")" << " ";
    }
    cout << endl;
    
    return 0;
}
