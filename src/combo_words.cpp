#include "combo_words.h"

#include "panelfile.h"

combo_words::combo_words() {}

void combo_words::Init() {
    if (this->field_0 == nullptr) {
        this->field_0 = PanelFile::UnmashPanelFile("combo_words", static_cast<panel_layer>(6));
        this->field_4 = *this->field_0->field_28.m_data;
        FEText **v3 = this->field_8;

        this->field_8[0] = this->field_0->GetTextPointer("combo_word_01");

        this->field_C = this->field_0->GetTextPointer("combo_word_02");

        this->field_10 = this->field_0->GetTextPointer("combo_word_03");

        this->field_14 = this->field_0->GetTextPointer("combo_word_04");

        this->field_18 = this->field_0->GetTextPointer("combo_word_05");

        this->field_1C = this->field_0->GetTextPointer("combo_word_06");

        this->field_20 = this->field_0->GetTextPointer("combo_word_07");
        this->field_8[0]->SetText(static_cast<global_text_enum>(408));
        this->field_C->SetText(static_cast<global_text_enum>(409));
        this->field_10->SetText(static_cast<global_text_enum>(410));
        this->field_14->SetText(static_cast<global_text_enum>(411));
        this->field_18->SetText(static_cast<global_text_enum>(412));
        this->field_1C->SetText(static_cast<global_text_enum>(413));
        this->field_20->SetText(static_cast<global_text_enum>(414));
        auto v18 = 7;
        do {
            (*v3)->SetNoFlash(color32{0xC8, 0xC8, 0xC8, 0xFF});
            (*v3)->SetShown(false);
            ++v3;
            --v18;
        } while (v18);
    }

    auto v19 = this->field_24;
    if (v19 > -1 && v19 < 7) {
        this->field_8[v19]->SetShown(false);
    }
}

void combo_words::DeInit() {
    if (this->field_0 != nullptr)
    {
        this->field_0 = nullptr;
    }
}
