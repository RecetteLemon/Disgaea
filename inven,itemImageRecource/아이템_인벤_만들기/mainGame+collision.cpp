#include "stdafx.h"
#include "mainGame.h"

//객체지향코딩방식이 나오면서
//하나의 헤더파일은 여러개 CPP파일을 거느릴 수 있게 되었는데
//게임프로그래밍 쪽은 워낙에 코드량이 많다 보니까
//헤더파일을 선언 후에 함수를 조각조각내서
//코드를 보기 편하게 짜는 게 가능해졌다
//

//1번 방식
void mainGame::collision()
{
	//바로 쉽에서 삭제해주게 되면 다른 객체에서 프로세스가 돌아가고 있을 경우
	//이유 없이 뻑이 나버리게 될 위험이 높다
	//따라서 바로 쉽에서 삭제를 해주기보다는 싸드 미사일 객체에게 지우라고
	//메시지만 주고 싸드 미사일 자체에서 지우게 하는게 안전


	for (int i = 0; i < _ship->getThaadMissile()->getVBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT temp;
			if (IntersectRect(&temp, &_ship->getThaadMissile()->getVBullet()[i].rc,
				&_em->getVMinion()[j]->getRect()))
			{
				_ship->getThaadMissile()->removeMissile(i);
				_em->removeMinion(j);
				break;
			}
		}
	}
}