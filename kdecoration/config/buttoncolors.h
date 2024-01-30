#ifndef BUTTONCOLORS_H
#define BUTTONCOLORS_H

/*
 * SPDX-FileCopyrightText: 2023 Paul A McAuley <kde@paulmcauley.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "breeze.h"
#include "breezesettings.h"
#include "colortools.h"
#include "decorationcolors.h"
#include "ui_buttoncolors.h"
#include <KColorButton>
#include <KDecoration2/DecorationButton>
#include <KDecoration2/DecorationSettings>
#include <QDialog>

namespace Breeze
{

struct ColumnsLoaded {
    bool active;
    bool inactive;
};

class ButtonColors : public QDialog
{
    Q_OBJECT

    friend class ConfigWidget;

public:
    explicit ButtonColors(KSharedConfig::Ptr config, KSharedConfig::Ptr presetsConfig, QWidget *parent = nullptr);
    ~ButtonColors();

    void loadMain(const bool assignUiValuesOnly = false);
    void save(const bool reloadKwinConfig = true);
    void defaults();

    bool event(QEvent *ev) override;

public Q_SLOTS:
    void load()
    {
        loadMain();
    }

private Q_SLOTS:
    void accept() override;
    void reject() override;
    void updateChanged();
    void saveAndReloadKWinConfig()
    {
        save(true);
    }
    void setApplyButtonState(const bool on);
    void showHideTranslucencySettingsActive()
    {
        showHideTranslucencySettings(true);
    }
    void showHideTranslucencySettingsInactive()
    {
        showHideTranslucencySettings(false);
    }
    void refreshCloseButtonIconColorStateActive()
    {
        refreshCloseButtonIconColorState(true);
    }
    void refreshCloseButtonIconColorStateInactive()
    {
        refreshCloseButtonIconColorState(false);
    }
    void setNegativeCloseBackgroundHoverPressStateActive()
    {
        setNegativeCloseBackgroundHoverPressState(true);
    }
    void setNegativeCloseBackgroundHoverPressStateInactive()
    {
        setNegativeCloseBackgroundHoverPressState(false);
    }
    void resizeOverrideColorTable();
    void showActiveOverrideGroupBox(const bool on);
    void showInactiveOverrideGroupBox(const bool on);
    void resizeDialog();
    void copyCellCheckedStatusToOtherTable();
    void copyCellColorDataToOtherCells();
    void loadButtonPaletteColorsIcons();
    void tableVerticalHeaderSectionClicked(const int row);
    void setTableVerticalHeaderSectionCheckedState(QTableWidget *table, const int row, const bool checked);
    void updateLockIcons();
    void loadHorizontalHeaderIcons();

Q_SIGNALS:
    void changed(bool);

private:
    void getButtonsOrderFromKwinConfig();
    QList<Breeze::DecorationButtonPalette *> sortButtonsAsPerKwinConfig(QList<Breeze::DecorationButtonPalette *> inputlist);

    void generateTableCells(QTableWidget *table);

    void setSystemTitlebarColors();
    void setOverrideComboBoxColorIcons(const bool active, DecorationColors &decorationColors);

    void refreshCloseButtonIconColorState(bool active);

    void setNegativeCloseBackgroundHoverPressState(bool active);

    void showHideTranslucencySettings(bool active);

    //* decodes closeButtonIconColor from the UI for as InternalSettings::EnumCloseButtonIconColor index for saving, taking into account the
    int convertCloseButtonIconColorUiToSettingsIndex(bool active, const int uiIndex);
    //* loads the current close button icon colour from m_internalSettings to UI
    void loadCloseButtonIconColor(bool active);
    //* given a settings index returns a UI index for the current m_closeButtonIconColorState
    int convertCloseButtonIconColorSettingsToUiIndex(bool active, const int settingsIndex);

    //* outputs pointers to the CheckBox, ComboBox, ColorButton and SpinBox at a given table cell. Returns true if they are valid
    bool checkBoxComboBoxColorButtonSpinBoxAtTableCell(const bool active,
                                                       const int column,
                                                       const int row,
                                                       QCheckBox *&outputCheckBox,
                                                       QComboBox *&outputComboBox,
                                                       KColorButton *&outputColorButton,
                                                       QSpinBox *&outputSpinBox);

    QByteArray encodeColorOverrideTableColumn(const int column, const bool active, const bool reset);
    bool decodeOverrideColorsAndLoadTableColumn(const QByteArray overrideColorColumnJson, const int column, const bool active);
    QByteArray encodeColorOverrideLockStates(const bool active);
    void decodeAndLoadColorOverrideLockStates(const bool active);

    void setHorizontalHeaderSectionIcon(KDecoration2::DecorationButtonType type, QTableWidget *table, int section);

    void loadButtonPaletteColorsIconsMain(bool active);

    void setChanged(bool value);
    bool isDefaults();

    Ui_ButtonColors *m_ui;

    InternalSettingsPtr m_internalSettings;
    KSharedConfig::Ptr m_configuration;
    KSharedConfig::Ptr m_presetsConfiguration;
    QObject *m_parent;

    //* changed state
    bool m_changed;

    //* defaults clicked
    bool m_defaultsPressed = false;

    bool m_loading = false;
    bool m_loaded = false;
    bool m_processingDefaults = false;

    ColumnsLoaded m_overrideColorsLoaded = {false, false};

    // strings for UI corresponding to overridableButtonTypes
    const QHash<KDecoration2::DecorationButtonType, QString> m_colorOverridableButtonTypesStrings{
        {KDecoration2::DecorationButtonType::Close, i18n("Close")},
        {KDecoration2::DecorationButtonType::Maximize, i18n("Maximize/Restore")},
        {KDecoration2::DecorationButtonType::Minimize, i18n("Minimize")},
        {KDecoration2::DecorationButtonType::ContextHelp, i18n("Help")},
        {KDecoration2::DecorationButtonType::Shade, i18n("Shade")},
        {KDecoration2::DecorationButtonType::OnAllDesktops, i18n("All desktops")},
        {KDecoration2::DecorationButtonType::KeepBelow, i18n("Keep Below")},
        {KDecoration2::DecorationButtonType::KeepAbove, i18n("Keep Above")},
        {KDecoration2::DecorationButtonType::ApplicationMenu, i18n("Application Menu")},
        {KDecoration2::DecorationButtonType::Menu, i18n("Menu")},
    };

    // strings for UI corresponding to enum OverridableButtonColorStates in breeze.h
    const QStringList m_overridableButtonColorStatesStrings{
        i18n("Icon pressed"),
        i18n("Icon hover"),
        i18n("Icon normal"),
        i18n("Background pressed"),
        i18n("Background hover"),
        i18n("Background normal"),
        i18n("Outline pressed"),
        i18n("Outline hover"),
        i18n("Outline normal"),
    };

    const QStringList m_overrideComboBoxItems = {i18n("Custom"),
                                                 i18n("Titlebar text, auto"),
                                                 i18n("Titlebar text, active"),
                                                 i18n("Titlebar text, inactive"),
                                                 i18n("Titlebar background, auto"),
                                                 i18n("Titlebar background, active"),
                                                 i18n("Titlebar background, inactive"),
                                                 i18n("Accent (button hover)"),
                                                 i18n("Accent (button focus)"),
                                                 i18n("Accent (highlight)"),
                                                 i18n("Accent (highlight, less saturated)"),
                                                 i18n("Negative text"),
                                                 i18n("Negative, less saturated"),
                                                 i18n("Negative, saturated"),
                                                 i18n("Negative, fully saturated"),
                                                 i18n("Neutral text"),
                                                 i18n("Neutral, less saturated"),
                                                 i18n("Neutral, saturated"),
                                                 i18n("Positive text"),
                                                 i18n("Positive, less saturated"),
                                                 i18n("Positive, saturated"),
                                                 i18n("White"),
                                                 i18n("Window outline, auto"),
                                                 i18n("Window outline, active"),
                                                 i18n("Window outline, inactive"),
                                                 i18n("Window shadow, auto"),
                                                 i18n("Window shadow, active"),
                                                 i18n("Window shadow, inactive")};

    enum struct CloseButtonIconColorState { AsSelected = 1, NegativeWhenHoveredPressed = 2, White = 4, WhiteWhenHoveredPressed = 8, COUNT };

    uint32_t m_closeButtonIconColorStateActive;
    uint32_t m_closeButtonIconColorStateInactive;
    QList<KDecoration2::DecorationButtonType> m_visibleButtonsOrder; // ordered visible buttons (visible + an added dummy Custom button used in the icon display
                                                                     // of the colour palette for "other" buttons)
    QList<KDecoration2::DecorationButtonType>
        m_hiddenButtons; // buttons that are not shown due to not being added in the "Titlebar buttons" section of the KDE Window decoration config
    QList<KDecoration2::DecorationButtonType> m_allCustomizableButtonsOrder; // user-ordered list of all buttons, including hidden appended at the end, not
                                                                             // including the dummy custom button added in m_visibleButtonsOrder
    QColor m_systemTitlebarTextActive;
    QColor m_systemTitlebarTextInactive;
    QColor m_systemTitlebarBackgroundActive;
    QColor m_systemTitlebarBackgroundInactive;
};

}

#endif // BUTTONCOLORS_H
