// TextRPG.cpp: 콘솔 응용  프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"

#include <windows.h>

#include "Scene.h"

#include "GameSystem.h"
#include "SceneManager.h"



typedef enum
{
	NOCURSOR,
	SOLIDCURSOR,
	NORMALCURSOR,

}CURSOR_TYPE;

void SetCursorType(CURSOR_TYPE _c);



int main()
{
	{
		// 콘솔창 크기 지정
		SetCursorType(CURSOR_TYPE::NOCURSOR);
	}

	{
		
		int iNextIndex = -1;
		int iIndex = 0;
		bool isGameProgress = true;
		GameSystem::GetInstance()->CharacterCreate(eCharacterType::PLAYER);
		GameSystem::GetInstance()->InitItemInfo();
		GameSystem::GetInstance()->SetIsGameProgress(isGameProgress);
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_TITLE, 0);

		while (true == GameSystem::GetInstance()->GetIsGameProgress())
		{
			SceneManager::GetInstance()->Update();
		}

		SceneManager::GetInstance()->Release();
		GameSystem::GetInstance()->Release();
		
	}
	_getch();

    return 0;
}



void SetCursorType(CURSOR_TYPE _c)
{
	CONSOLE_CURSOR_INFO CurInfo;

	switch (_c)
	{
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = FALSE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}
