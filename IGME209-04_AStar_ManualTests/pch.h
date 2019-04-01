// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

__declspec(dllimport) char* GetTeam();
__declspec(dllimport) bool SetMaze(const int** data, int width, int height);
__declspec(dllimport) int** GetMaze(int& width, int& height);
__declspec(dllimport) bool GetNextPosition(int& xpos, int& ypos);
__declspec(dllimport) bool SetStart(int xpos, int ypos);
__declspec(dllimport) bool GetStart(int& xpos, int& ypos);
__declspec(dllimport) bool SetEnd(int xpos, int ypos);
__declspec(dllimport) bool GetEnd(int& xpos, int& ypos);
__declspec(dllimport) void Restart();

void SetRemoteStart(int*);
void SetRemoteEnd(int*);
void GetRemoteStart(int*);
void GetRemoteEnd(int*);

#endif //PCH_H
