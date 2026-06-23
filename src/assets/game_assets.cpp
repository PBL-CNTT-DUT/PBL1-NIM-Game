#include "assets/game_assets.h"

namespace {

    constexpr const char* musicBgmPath = "assets/music/beanfeast.mp3";
    constexpr const char* soundClickPath = "assets/music/Click1B.mp3";
    constexpr const char* soundEndGamePath = "assets/music/Retro_Success.wav";
    
    constexpr const char* bgMainMenuPath = "assets/images/bg_main_menu.png";
    constexpr const char* bgMatchSetupPath = "assets/images/bg_match_setup.png";
    constexpr const char* bgPlayPath = "assets/images/bg_play.png";
    constexpr const char* bgSettingPath = "assets/images/bg_setting.png";
    constexpr const char* bgHelpPath = "assets/images/bg_help.png";

    constexpr const char* btnNormalPath = "assets/ui/button/btn_normal.png";
    constexpr const char* btnHoverPath = "assets/ui/button/btn_hover.png";
    constexpr const char* btnPressedPath = "assets/ui/button/btn_pressed.png";
    constexpr const char* btnSelectedPath = "assets/ui/button/btn_selected.png";

    constexpr const char* decreaseBtnPath = "assets/ui/button/btn_minus.png";
    constexpr const char* decreaseBtnNormalPath = decreaseBtnPath;
    constexpr const char* decreaseBtnHoverPath = decreaseBtnPath;
    constexpr const char* decreaseBtnPressedPath = decreaseBtnPath;
    constexpr const char* decreaseBtnSelectedPath = decreaseBtnPath;

    constexpr const char* increaseBtnPath = "assets/ui/button/btn_plus.png";
    constexpr const char* increaseBtnNormalPath = increaseBtnPath;
    constexpr const char* increaseBtnHoverPath = increaseBtnPath;
    constexpr const char* increaseBtnPressedPath = increaseBtnPath;
    constexpr const char* increaseBtnSelectedPath = increaseBtnPath;

    constexpr const char* pauseBtnPath = "assets/ui/button/Pause.png";
    constexpr const char* pauseBtnNormalPath = pauseBtnPath;
    constexpr const char* pauseBtnHoverPath = pauseBtnPath;
    constexpr const char* pauseBtnPressedPath = pauseBtnPath;
    constexpr const char* pauseBtnSelectedPath = pauseBtnPath;

    constexpr const char* settingBtnPath = "assets/ui/button/setting.png";
    constexpr const char* settingBtnNormalPath = settingBtnPath;
    constexpr const char* settingBtnHoverPath = settingBtnPath;
    constexpr const char* settingBtnPressedPath = settingBtnPath;
    constexpr const char* settingBtnSelectedPath = settingBtnPath;

    constexpr const char* musicOnBtnPath = "assets/ui/button/Music_on.png";
    constexpr const char* musicOnBtnNormalPath = musicOnBtnPath;
    constexpr const char* musicOnBtnHoverPath = musicOnBtnPath;
    constexpr const char* musicOnBtnPressedPath = musicOnBtnPath;
    constexpr const char* musicOnBtnSelectedPath = musicOnBtnPath;

    constexpr const char* musicOffBtnPath = "assets/ui/button/Music_off.png";
    constexpr const char* musicOffBtnNormalPath = musicOffBtnPath;
    constexpr const char* musicOffBtnHoverPath = musicOffBtnPath;
    constexpr const char* musicOffBtnPressedPath = musicOffBtnPath;
    constexpr const char* musicOffBtnSelectedPath = musicOffBtnPath;

    constexpr const char* musicIncreaseBtnPath = "assets/ui/button/music+.png";
    constexpr const char* musicIncreaseBtnNormalPath = musicIncreaseBtnPath;
    constexpr const char* musicIncreaseBtnHoverPath = musicIncreaseBtnPath;
    constexpr const char* musicIncreaseBtnPressedPath = musicIncreaseBtnPath;
    constexpr const char* musicIncreaseBtnSelectedPath = musicIncreaseBtnPath;

    constexpr const char* musicDecreaseBtnPath = "assets/ui/button/music-.png";
    constexpr const char* musicDecreaseBtnNormalPath = musicDecreaseBtnPath;
    constexpr const char* musicDecreaseBtnHoverPath = musicDecreaseBtnPath;
    constexpr const char* musicDecreaseBtnPressedPath = musicDecreaseBtnPath;
    constexpr const char* musicDecreaseBtnSelectedPath = musicDecreaseBtnPath;

    constexpr const char* soundOnBtnPath = "assets/ui/button/Sound_on.png";
    constexpr const char* soundOnBtnNormalPath = soundOnBtnPath;
    constexpr const char* soundOnBtnHoverPath = soundOnBtnPath;
    constexpr const char* soundOnBtnPressedPath = soundOnBtnPath;
    constexpr const char* soundOnBtnSelectedPath = soundOnBtnPath;

    constexpr const char* soundOffBtnPath = "assets/ui/button/Sound_off.png";
    constexpr const char* soundOffBtnNormalPath = soundOffBtnPath;
    constexpr const char* soundOffBtnHoverPath = soundOffBtnPath;
    constexpr const char* soundOffBtnPressedPath = soundOffBtnPath;
    constexpr const char* soundOffBtnSelectedPath = soundOffBtnPath;

    constexpr const char* soundIncreaseBtnPath = "assets/ui/button/sound+.png";
    constexpr const char* soundIncreaseBtnNormalPath = soundIncreaseBtnPath;
    constexpr const char* soundIncreaseBtnHoverPath = soundIncreaseBtnPath;
    constexpr const char* soundIncreaseBtnPressedPath = soundIncreaseBtnPath;
    constexpr const char* soundIncreaseBtnSelectedPath = soundIncreaseBtnPath;

    constexpr const char* soundDecreaseBtnPath = "assets/ui/button/sound-.png";
    constexpr const char* soundDecreaseBtnNormalPath = soundDecreaseBtnPath;
    constexpr const char* soundDecreaseBtnHoverPath = soundDecreaseBtnPath;
    constexpr const char* soundDecreaseBtnPressedPath = soundDecreaseBtnPath;
    constexpr const char* soundDecreaseBtnSelectedPath = soundDecreaseBtnPath;

    constexpr const char* yesBtnPath = "assets/ui/button/yes.png";
    constexpr const char* yesBtnNormalPath = yesBtnPath;
    constexpr const char* yesBtnHoverPath = yesBtnPath;
    constexpr const char* yesBtnPressedPath = yesBtnPath;
    constexpr const char* yesBtnSelectedPath = yesBtnPath;

    constexpr const char* noBtnPath = "assets/ui/button/no.png";
    constexpr const char* noBtnNormalPath = noBtnPath;
    constexpr const char* noBtnHoverPath = noBtnPath;
    constexpr const char* noBtnPressedPath = noBtnPath;
    constexpr const char* noBtnSelectedPath = noBtnPath;

    constexpr const char* playLimitSwitchOffPath = "assets/ui/button/btn_switch_off.png";
    constexpr const char* playLimitSwitchOnPath = "assets/ui/button/btn_switch_on.png";
    
    constexpr const char* fontTitlePath = "assets/fonts/pixelFont-7-8x14-sproutLands.ttf";
    constexpr const char* fontCommonPath = "assets/fonts/SVN-New-Athletic-M54.ttf";

    constexpr const char* cloudNormalPath   = "assets/ui/cloud_single/cloud4.png";
    constexpr const char* cloudHoverPath    = "assets/ui/cloud_single/cloud5.png";
    constexpr const char* cloudPressedPath  = "assets/ui/cloud_single/cloud5.png";
    constexpr const char* cloudSelectedPath = "assets/ui/cloud_single/cloud6.png";

    
    bool _is_texture_valid(Texture2D t) {
        return t.id != 0;
    }

    bool _is_font_valid(Font f) {
        return f.texture.id != 0;
    }

    bool _has_any_button_texture(const UIButtonStateTextures& textures) {
        return _is_texture_valid(textures.normal) ||
               _is_texture_valid(textures.hover) ||
               _is_texture_valid(textures.pressed) ||
               _is_texture_valid(textures.selected);
    }
    
    bool _load_texture_if_exists(Texture2D& out, const char* path) {
        out = {};

        if (path == nullptr || !FileExists(path)) {
            return false;
        }

        out = LoadTexture(path);
        if (!_is_texture_valid(out)) {
            return false;
        }

        SetTextureFilter(out, TEXTURE_FILTER_POINT);
        return true;
    }

    void _unload_if_loaded(Texture2D& tex) {
        if (_is_texture_valid(tex)) {
            UnloadTexture(tex);
        }
        tex = {};
    }

    void _unload_if_loaded(UISwitchTextures& tex) {
        _unload_if_loaded(tex.off);
        _unload_if_loaded(tex.on);
    }
    void _unload_if_loaded(Font& font, bool& owned) {
        if (owned && _is_font_valid(font)) {
            UnloadFont(font);
        }

        font = {};
        owned = false;
    }

  

    bool _load_music_if_exists(Music& out, const char* path, float volume) {
        if (path == nullptr || !FileExists(path)) {
            out = {};
            return false;
        }

        out = LoadMusicStream(path);
        if (out.frameCount <= 0) {
            return false;
        }

        SetMusicVolume(out, volume);
        return true;
    }

    bool _load_sound_if_exists(Sound& out, const char* path, float volume) {
        if (path == nullptr || !FileExists(path)) {
            out = {};
            return false;
        }

        out = LoadSound(path);
        if (out.frameCount <= 0) {
            return false;
        }

        SetSoundVolume(out, volume);
        return true;
    }

    void _unload_if_loaded(Music& music) {
        if (music.frameCount > 0) {
            UnloadMusicStream(music);
        }
        music = {};
    }

    void _unload_if_loaded(Sound& sound) {
        if (sound.frameCount > 0) {
            UnloadSound(sound);
        }
        sound = {};
    }

    

    void _unload_button_textures(UIButtonStateTextures& btn) {
        _unload_if_loaded(btn.normal);
        _unload_if_loaded(btn.hover);
        _unload_if_loaded(btn.pressed);
        _unload_if_loaded(btn.selected);
    }

    bool _game_assets_load_button_textures_from_multiple_pngs(
        UIButtonStateTextures& out,
        const char* normalPath,
        const char* hoverPath,
        const char* pressedPath,
        const char* selectedPath
    ) {
        out = {};

        _load_texture_if_exists(out.normal, normalPath);
        _load_texture_if_exists(out.hover, hoverPath);
        _load_texture_if_exists(out.pressed, pressedPath);
        _load_texture_if_exists(out.selected, selectedPath);

        return _has_any_button_texture(out);
    }

    bool _load_font_if_exists(Font& out, bool& owned, const char* path) {
        out = {};
        owned = false;
        
        if (path == nullptr || !FileExists(path)) {
            return false;
        }

        const char* allChars = u8" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,?!:;+-=*/()<>[]{}@#$%^&*_\"'\\àáạảãâầấậẩẫăằắặẳẵèéẹẻẽêềếệểễìíịỉĩòóọỏõôồốộổỗơờớợởỡùúụủũưừứựửữỳýỵỷỹđÀÁẠẢÃÂẦẤẬẨẪĂẰẮẶẲẴÈÉẸẺẼÊỀẾỆỂỄÌÍỊỈĨÒÓỌỎÕÔỒỐỘỔỖƠỜỚỢỞỠÙÚỤỦŨƯỪỨỰỬỮỲÝỴỶỸĐ";

        int codepointsCount = 0;
        int* codepoints = LoadCodepoints(allChars, &codepointsCount);

        out = LoadFontEx(path, 128, codepoints, codepointsCount);

        if (codepoints != nullptr) {
            UnloadCodepoints(codepoints);
        }

        if (!_is_font_valid(out)) {
            return false;
        }

        SetTextureFilter(out.texture, TEXTURE_FILTER_POINT);
        owned = true;
        return true;
    }

    bool _load_switch_if_exists(UISwitchTextures& out, const char* offPath, const char* onPath) {
        out = {};

        _load_texture_if_exists(out.off, offPath);
        _load_texture_if_exists(out.on, onPath);

        return _is_texture_valid(out.off) && _is_texture_valid(out.on);
    }


   

    bool _load_all_audio() {
        const bool musicBgmOk = _load_music_if_exists(g_assets.musics.bgm, musicBgmPath, 0.1f);
        if (musicBgmOk) {
            PlayMusicStream(g_assets.musics.bgm);
        }
        const bool soundClickOk = _load_sound_if_exists(g_assets.sounds.click, soundClickPath, 0.55f);
        const bool soundEndOk   = _load_sound_if_exists(g_assets.sounds.end,   soundEndGamePath, 0.7f);
        return musicBgmOk && soundClickOk && soundEndOk;
    }

    void _unload_all_textures() {
        _unload_if_loaded(g_assets.images.bg_main_menu);
        _unload_if_loaded(g_assets.images.bg_match_setup);
        _unload_if_loaded(g_assets.images.bg_play);
        _unload_if_loaded(g_assets.images.bg_setting);
        _unload_if_loaded(g_assets.images.bg_help);

        _unload_button_textures(g_assets.buttons.common);
        _unload_button_textures(g_assets.buttons.cloud);
        _unload_button_textures(g_assets.buttons.decrease);
        _unload_button_textures(g_assets.buttons.increase);
        _unload_button_textures(g_assets.buttons.pause);
        _unload_button_textures(g_assets.buttons.setting);
        _unload_button_textures(g_assets.buttons.music_on);
        _unload_button_textures(g_assets.buttons.music_off);
        _unload_button_textures(g_assets.buttons.music_increase);
        _unload_button_textures(g_assets.buttons.music_decrease);
        _unload_button_textures(g_assets.buttons.sound_on);
        _unload_button_textures(g_assets.buttons.sound_off);
        _unload_button_textures(g_assets.buttons.sound_increase);
        _unload_button_textures(g_assets.buttons.sound_decrease);
        _unload_button_textures(g_assets.buttons.yes);
        _unload_button_textures(g_assets.buttons.no);

        _unload_if_loaded(g_assets.switches.play_limit);
    }

    void _unload_all_fonts() {
        _unload_if_loaded(g_assets.fonts.common, g_assets.fonts.ownsCommon);
        _unload_if_loaded(g_assets.fonts.title,  g_assets.fonts.ownsTitle);
    }

    void _unload_all_audio() {
        _unload_if_loaded(g_assets.musics.bgm);
        _unload_if_loaded(g_assets.sounds.click);
        _unload_if_loaded(g_assets.sounds.end);
    }

} // namespace k ten






bool game_assets_load() {
    if (g_assets.loaded) {
        return true;
    }

    bool bgMainMenuOk = _load_texture_if_exists(g_assets.images.bg_main_menu, bgMainMenuPath);
    bool bgMatchSetupOk = _load_texture_if_exists(g_assets.images.bg_match_setup, bgMatchSetupPath);
    bool bgPlayOk = _load_texture_if_exists(g_assets.images.bg_play, bgPlayPath);
    bool bgSettingOk = _load_texture_if_exists(g_assets.images.bg_setting, bgSettingPath);
    bool bgHelpOk = _load_texture_if_exists(g_assets.images.bg_help, bgHelpPath);

    bool btnCommonOk = _game_assets_load_button_textures_from_multiple_pngs(
        g_assets.buttons.common,
        btnNormalPath,
        btnHoverPath,
        btnPressedPath,
        btnSelectedPath
    );
    bool btnCloudOk = _game_assets_load_button_textures_from_multiple_pngs(
        g_assets.buttons.cloud,
        cloudNormalPath,
        cloudHoverPath,
        cloudPressedPath,
        cloudSelectedPath
    );
    bool btnDecreaseOk = _game_assets_load_button_textures_from_multiple_pngs(
        g_assets.buttons.decrease,
        decreaseBtnNormalPath,
        decreaseBtnHoverPath,
        decreaseBtnPressedPath,
        decreaseBtnSelectedPath
    );

    bool btnIncreaseOk = _game_assets_load_button_textures_from_multiple_pngs(
        g_assets.buttons.increase,
        increaseBtnNormalPath,
        increaseBtnHoverPath,
        increaseBtnPressedPath,
        increaseBtnSelectedPath
    );

    bool btnPauseOk = _game_assets_load_button_textures_from_multiple_pngs(
        g_assets.buttons.pause,
        pauseBtnNormalPath,
        pauseBtnHoverPath,
        pauseBtnPressedPath,
        pauseBtnSelectedPath
    );

    bool btnSettingOk = _game_assets_load_button_textures_from_multiple_pngs(
        g_assets.buttons.setting,
        settingBtnNormalPath,
        settingBtnHoverPath,
        settingBtnPressedPath,
        settingBtnSelectedPath
    );

    bool btnMusicOnOk = _game_assets_load_button_textures_from_multiple_pngs(
        g_assets.buttons.music_on,
        musicOnBtnNormalPath,
        musicOnBtnHoverPath,
        musicOnBtnPressedPath,
        musicOnBtnSelectedPath
    );

    bool btnMusicOffOk = _game_assets_load_button_textures_from_multiple_pngs(
        g_assets.buttons.music_off,
        musicOffBtnNormalPath,
        musicOffBtnHoverPath,
        musicOffBtnPressedPath,
        musicOffBtnSelectedPath
    );

    bool btnMusicIncreaseOk = _game_assets_load_button_textures_from_multiple_pngs(
        g_assets.buttons.music_increase,
        musicIncreaseBtnNormalPath,
        musicIncreaseBtnHoverPath,
        musicIncreaseBtnPressedPath,
        musicIncreaseBtnSelectedPath
    );

    bool btnMusicDecreaseOk = _game_assets_load_button_textures_from_multiple_pngs(
        g_assets.buttons.music_decrease,
        musicDecreaseBtnNormalPath,
        musicDecreaseBtnHoverPath,
        musicDecreaseBtnPressedPath,
        musicDecreaseBtnSelectedPath
    );

    bool btnSoundOnOk = _game_assets_load_button_textures_from_multiple_pngs(
        g_assets.buttons.sound_on,
        soundOnBtnNormalPath,
        soundOnBtnHoverPath,
        soundOnBtnPressedPath,
        soundOnBtnSelectedPath
    );

    bool btnSoundOffOk = _game_assets_load_button_textures_from_multiple_pngs(
        g_assets.buttons.sound_off,
        soundOffBtnNormalPath,
        soundOffBtnHoverPath,
        soundOffBtnPressedPath,
        soundOffBtnSelectedPath
    );

    bool btnSoundIncreaseOk = _game_assets_load_button_textures_from_multiple_pngs(
        g_assets.buttons.sound_increase,
        soundIncreaseBtnNormalPath,
        soundIncreaseBtnHoverPath,
        soundIncreaseBtnPressedPath,
        soundIncreaseBtnSelectedPath
    );

    bool btnSoundDecreaseOk = _game_assets_load_button_textures_from_multiple_pngs(
        g_assets.buttons.sound_decrease,
        soundDecreaseBtnNormalPath,
        soundDecreaseBtnHoverPath,
        soundDecreaseBtnPressedPath,
        soundDecreaseBtnSelectedPath
    );

    bool btnYesOk = _game_assets_load_button_textures_from_multiple_pngs(
        g_assets.buttons.yes,
        yesBtnNormalPath,
        yesBtnHoverPath,
        yesBtnPressedPath,
        yesBtnSelectedPath
    );

    bool btnNoOk = _game_assets_load_button_textures_from_multiple_pngs(
        g_assets.buttons.no,
        noBtnNormalPath,
        noBtnHoverPath,
        noBtnPressedPath,
        noBtnSelectedPath
    );

    bool btnPlaySwitchOk = _load_switch_if_exists(
        g_assets.switches.play_limit,
        playLimitSwitchOffPath,
        playLimitSwitchOnPath
    );

    bool commonFontOk = _load_font_if_exists(
        g_assets.fonts.common,
        g_assets.fonts.ownsCommon,
        fontCommonPath
    );
    bool titleFontOk = _load_font_if_exists(
        g_assets.fonts.title,
        g_assets.fonts.ownsTitle,
        fontTitlePath
    );

    if (!commonFontOk) {
        g_assets.fonts.common = GetFontDefault();
        g_assets.fonts.ownsCommon = false;
    }
    if (!titleFontOk) {
        g_assets.fonts.title = GetFontDefault();
        g_assets.fonts.ownsTitle = false;
    }

    const bool audioOk = _load_all_audio();

    const bool allAssetsLoaded =
        bgMainMenuOk &&
        bgMatchSetupOk &&
        bgPlayOk &&
        btnCommonOk &&
        btnCloudOk &&
        btnPlaySwitchOk &&
        commonFontOk &&
        titleFontOk &&
        audioOk;
    
    g_assets.loaded = true;
    return allAssetsLoaded;
}

void game_assets_unload() {
    _unload_all_textures();
    _unload_all_fonts();
    _unload_all_audio();
    g_assets = {};
}
