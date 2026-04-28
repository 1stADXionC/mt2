#include "stdafx.h"
#ifdef ENABLE_MEMLEKET_SYSTEM
#include "../../common/service.h"
#include "../../common/length.h"
#include "../../common/tables.h"
#include "packet.h"
#include "MemleketTitle.h"
#include "buffer_manager.h"
#include "char.h"
#include "db.h"
#include "desc.h"
#include "constants.h"

namespace
{
	const CMemleketTitle::TBonusData s_aTitleBonus[19] =
	{
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 0
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 1
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 2
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 3
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 4
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 5
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 6
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 7
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 8
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 9
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 10
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 11
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 12
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 13
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 14
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 15
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 16
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }, // 17
		{ APPLY_MAX_HP, 1000, APPLY_NONE, 0, APPLY_NONE, 0 }  // 18
	};
}

auto CMemleketTitle::ClearBonusAffects(LPCHARACTER ch) -> void
{
	if (!ch)
		return;

	for (uint16_t i = AFFECT_MEMLEKET1; i <= AFFECT_MEMLEKET3; ++i)
		ch->RemoveAffect(i);
}

auto CMemleketTitle::ApplyBonusAffects(LPCHARACTER ch, int8_t bonusIdx) -> void
{
	if (!ch)
		return;

	if (bonusIdx < 0 || bonusIdx >= CHARACTER::MEMLEKET_MAX_NUM)
		return;

	const TBonusData& bonus = s_aTitleBonus[bonusIdx];

	ch->AddAffect(
		AFFECT_MEMLEKET1,
		aApplyInfo[bonus.applyType1].bPointType,
		bonus.applyValue1,
		0,
		INFINITE_AFFECT_DURATION,
		0,
		false
	);

	ch->AddAffect(
		AFFECT_MEMLEKET2,
		aApplyInfo[bonus.applyType2].bPointType,
		bonus.applyValue2,
		0,
		INFINITE_AFFECT_DURATION,
		0,
		false
	);

	ch->AddAffect(
		AFFECT_MEMLEKET3,
		aApplyInfo[bonus.applyType3].bPointType,
		bonus.applyValue3,
		0,
		INFINITE_AFFECT_DURATION,
		0,
		false
	);
}

auto CMemleketTitle::SelectTitle(const int8_t titleIDX, LPCHARACTER ch) -> void
{
	if (!ch || !ch->GetDesc())
		return;

	if (titleIDX < -1 || titleIDX >= CHARACTER::MEMLEKET_MAX_NUM)
		return;

	UpdateTitle(ch, titleIDX);
	SendToClient(ch);
}

auto CMemleketTitle::SelectBonus(const int8_t titleIDX, LPCHARACTER ch) -> void
{
	if (!ch || !ch->GetDesc())
		return;

	if (titleIDX < -1 || titleIDX >= CHARACTER::MEMLEKET_MAX_NUM)
		return;

	UpdateBonus(ch, titleIDX);
	SendToClient(ch);
}

auto CMemleketTitle::UpdateTitle(LPCHARACTER ch, const int8_t changeIdx) -> void
{
	if (!ch || !ch->GetDesc())
		return;

	if (changeIdx < -1 || changeIdx >= CHARACTER::MEMLEKET_MAX_NUM)
		return;

	ch->SetMemleket(changeIdx);
}

auto CMemleketTitle::UpdateBonus(LPCHARACTER ch, const int8_t changeIdx) -> void
{
	if (!ch || !ch->GetDesc())
		return;

	if (changeIdx < -1 || changeIdx >= CHARACTER::MEMLEKET_MAX_NUM)
		return;

	ClearBonusAffects(ch);
	ch->SetMemleketBonus(changeIdx);

	if (changeIdx == -1)
	{
		ch->ComputePoints();
		ch->PointsPacket();
		return;
	}

	ApplyBonusAffects(ch, changeIdx);

	ch->ComputePoints();
	ch->PointsPacket();
}

auto CMemleketTitle::SendToClient(LPCHARACTER ch) -> void
{
	if (!ch || !ch->GetDesc())
		return;

	TPacketGCMemleketState p;
	p.bMemleket = ch->GetMemleket();
	p.bMemleketBonus = ch->GetMemleketBonus();

	ch->GetDesc()->Packet(&p, sizeof(TPacketGCMemleketState));
}

#endif