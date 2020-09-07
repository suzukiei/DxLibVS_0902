#include "DxLib.h"

#define GAME_WIDTH 800 //��ʉ��̑傫��
#define GAME_HEIGHT 600 //��ʏc�̑傫��
#define GAME_COLOR 32 //��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR 0 //�^�C�g���o�[�̓f�t�H���g
#define GAME_WINDOW_NAME "GAME_TITLE" 

#define MOVIE_PATH ".\\Movie\\Fireworks.mp4"

int handle = -1; //����̃n���h��

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE); //log.txt���o�͂��Ȃ�
	ChangeWindowMode(TRUE); //�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR); //�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR); //�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME)); //�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE); //��A�N�e�B�u�ł����s����

	if (DxLib_Init() == -1) { return -1; } //DxLib�̏���������

	handle = LoadGraph(MOVIE_PATH);

	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; } //���b�Z�[�W�����̌��ʂ��G���[�\���̎��A�����I��
		if (ClearDrawScreen() != 0) { break; } //��ʂ������ł��Ȃ��������A�����I��

		if (GetMovieStateToGraph(handle) == 0)
		{
			SeekMovieToGraph(handle, 0); //�Đ��o�[���ŏ�����ɂ���
			PlayMovieToGraph(handle); //������Đ���Ԃɂ���

			ChangeMovieVolumeToGraph(127,handle)//����̉��𒲐�����
		}
		DrawExtendGraph(0, 0, GAME_WIDTH, GAME_HEIGHT, handle, FALSE);

		DrawString(0, 0, "������Đ����Ă��܂��E�E�E", GetColor(255, 255, 255));

		ScreenFlip(); //���j�^�̃��t���b�V�����[�g�̂͂₳�ŗ���ʂ��ĕ`��
	}

	DxLib_End();

	DeleteGraph(handle);

	return 0;
}