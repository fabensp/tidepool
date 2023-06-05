#ifndef TIDEPOOLBASE_H
#define TIDEPOOLBASE_H

#include <QPalette>

namespace {

class Theme {

public:
    /**
     * @brief Current currently selected palette of the application interface
     */
    static QPalette Current;

    /**
     * @brief Froth - cloudy gray
     */
    static const QPalette Froth;

    /**
     * @brief DeepSea - teal
     */
    static const QPalette DeepSea;

    /**
     * @brief Ocean - light blue, hint of green/gray
     */
    static const QPalette Ocean;

    /**
     * @brief Seaweed - gray green
     */
    static const QPalette Seaweed;

    /**
     * @brief Beach - beige
     */
    static const QPalette Beach;

    /**
     * @brief Riverbed - light blue
     */
    static const QPalette Riverbed;

    /**
     * @brief Jelly - desaturated light violet
     */
    static const QPalette Jelly;

    /**
     * @brief Coral - pink
     */
    static const QPalette Coral;

    /**
     * @brief get returns the palette at the index
     * @param i index 0-7
     * @return palette pointer
     */
    static const QPalette* get(int i) { return Themes[i]; }

private:
    static const QPalette* Themes[8];
};

const QPalette Theme::Froth(QColor::fromRgb(170, 180, 185));
const QPalette Theme::DeepSea(QColor::fromRgb(108, 163, 163));
const QPalette Theme::Ocean(QColor::fromRgb(99, 150, 173));
const QPalette Theme::Seaweed(QColor::fromRgb(108, 145, 131));
const QPalette Theme::Beach(QColor::fromRgb(181, 172, 143));
const QPalette Theme::Riverbed(QColor::fromRgb(141, 168, 186));
const QPalette Theme::Jelly(QColor::fromRgb(187, 165, 194));
const QPalette Theme::Coral(QColor::fromRgb(227, 168, 188));

QPalette Theme::Current = Theme::Froth;

const QPalette* Theme::Themes[8] = {&Froth, &DeepSea,  &Ocean, &Seaweed,
                                    &Beach, &Riverbed, &Jelly, &Coral};
} // namespace

#endif // TIDEPOOLBASE_H
