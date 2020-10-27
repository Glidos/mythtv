#ifndef MYTHPLAYERCAPTIONSUI_H
#define MYTHPLAYERCAPTIONSUI_H

// MythTV
#include "mythplayervideoui.h"

class MTV_PUBLIC MythPlayerCaptionsUI : public MythPlayerVideoUI
{
  public:
    MythPlayerCaptionsUI(MythMainWindow* MainWindow, TV* Tv, PlayerContext* Context, PlayerFlags Flags);
   ~MythPlayerCaptionsUI() override;

    void ResetCaptions();
    bool ToggleCaptions();
    bool ToggleCaptions(uint Type) override;
    bool HasTextSubtitles();
    void SetCaptionsEnabled(bool Enable, bool UpdateOSD = true);
    bool GetCaptionsEnabled() const;
    virtual void DisableCaptions(uint Mode, bool UpdateOSD = true);
    void EnableCaptions(uint Mode, bool UpdateOSD = true) override;

    // N.B. These methods handle audio tracks as well. Fix.
    QStringList GetTracks(uint Type);
    uint GetTrackCount(uint Type);
    virtual int SetTrack(uint Type, uint TrackNo);
    int  GetTrack(uint Type);
    int  ChangeTrack(uint Type, int Direction);

    void ChangeCaptionTrack(int Direction);
    bool HasCaptionTrack(uint Mode);
    uint NextCaptionTrack(uint Mode);
    void DoDisableForcedSubtitles();
    void DoEnableForcedSubtitles();

    void EnableTeletext(int Page = 0x100);
    void DisableTeletext();
    void ResetTeletext();
    bool HandleTeletextAction(const QString &Action);
    void SetTeletextPage(uint Page);

    void ReinitOSD() override;
    InteractiveTV* GetInteractiveTV() override;
    bool ITVHandleAction(const QString& Action);
    void ITVRestart(uint Chanid, uint Cardid, bool IsLiveTV);

  protected:
    InteractiveTV *m_interactiveTV { nullptr };
    QMutex m_itvLock  { };
    bool m_itvEnabled { false };
    bool m_itvVisible { false };
};

#endif
