#pragma once
class CMemleketTitle : public singleton<CMemleketTitle>
{
public:
	CMemleketTitle() = default;
	~CMemleketTitle() = default;

	struct TBonusData
	{
		BYTE applyType1;
		long applyValue1;

		BYTE applyType2;
		long applyValue2;

		BYTE applyType3;
		long applyValue3;
	};

	auto SelectTitle(int8_t titleIDX, LPCHARACTER ch) -> void;
	auto SelectBonus(int8_t titleIDX, LPCHARACTER ch) -> void;

	auto UpdateTitle(LPCHARACTER ch, int8_t changeIdx = -1) -> void;
	auto UpdateBonus(LPCHARACTER ch, int8_t changeIdx = -1) -> void;

	auto ClearBonusAffects(LPCHARACTER ch) -> void;
	auto ApplyBonusAffects(LPCHARACTER ch, int8_t bonusIdx) -> void;
	auto SendToClient(LPCHARACTER ch) -> void;
};