#pragma once
void initShowMsg(SHORT x, SHORT y);
void show_msg(char *msgs);
void ClrMsg(void);
void GotoXY(SHORT x, SHORT y);
void GetXY(int* x, int* y);
void initShowMsg_C(int id, SHORT x, SHORT y, int LBR);
void ClrMsg_C(int  id, int LBR);
void show_msg_C(int id, char* msgs, int LBR);

