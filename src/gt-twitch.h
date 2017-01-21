#ifndef GT_TWITCH_H
#define GT_TWITCH_H

#include <gtk/gtk.h>

#define MAX_QUERY 30
#define NO_GAME ""

G_BEGIN_DECLS

#define GT_TYPE_TWITCH (gt_twitch_get_type())

G_DECLARE_FINAL_TYPE(GtTwitch, gt_twitch, GT, TWITCH, GObject)

typedef enum _GtTwitchError
{
    GT_TWITCH_ERROR_SOUP,
    GT_TWITCH_ERROR_JSON,
} GtTwitchError;

typedef enum _GtTwitchStreamQuality
{
    GT_TWITCH_STREAM_QUALITY_SOURCE,
    GT_TWITCH_STREAM_QUALITY_HIGH,
    GT_TWITCH_STREAM_QUALITY_MEDIUM,
    GT_TWITCH_STREAM_QUALITY_LOW,
    GT_TWITCH_STREAM_QUALITY_MOBILE,
    GT_TWITCH_STREAM_QUALITY_AUDIO_ONLY
} GtTwitchStreamQuality;

struct _GtTwitch
{
    GObject parent_instance;
};

typedef struct _GtTwitchStreamAccessToken
{
    gchar* token;
    gchar* sig;
} GtTwitchStreamAccessToken;

typedef struct _GtTwitchStreamData
{
    gint width;
    gint height;
    glong bandwidth;
    GtTwitchStreamQuality quality;
    gchar* url;
} GtTwitchStreamData;

typedef struct _GtChannelRawData
{
    gint64 id;
    gchar* game;
    gint64 viewers;
    GDateTime* stream_started_time;
    gchar* status;
    gchar* name;
    gchar* display_name;
    gchar* preview_url;
    gchar* video_banner_url;
    gboolean online;
} GtChannelRawData;

typedef struct _GtGameRawData
{
    gint64 id;
    gchar* name;
    gchar* preview_url;
    GdkPixbuf* logo;
    gint64 viewers;
    gint64 channels;
} GtGameRawData;

typedef struct
{
    gchar* name;
    gchar* version;
    GdkPixbuf* pixbuf;
} GtChatBadge;

typedef struct
{
    gint id;
    gchar* code;
    gint set;
    GdkPixbuf* pixbuf;

    //NOTE: These are only set if coming from GtIrc
    gint start; // Start of text to replace
    gint end; // End of text to replace
} GtChatEmote;

typedef enum _GtTwitchChannelInfoPanelType
{
    GT_TWITCH_CHANNEL_INFO_PANEL_TYPE_DEFAULT,
    GT_TWITCH_CHANNEL_INFO_PANEL_TYPE_TEESPRING,
} GtTwitchChannelInfoPanelType;

typedef struct _GtTwitchChannelInfoPanel
{
    GtTwitchChannelInfoPanelType type;
    gchar* title;
    gchar* html_description;
    gchar* markdown_description;
    GdkPixbuf* image;
    gchar* link;
    gint64 order;
} GtTwitchChannelInfoPanel;

typedef struct _GtTwitchOAuthInfo
{
    gchar* user_name;
    GList* scopes;
} GtTwitchOAuthInfo;

GtTwitch*                  gt_twitch_new(void);
void                       gt_twitch_stream_access_token_free(GtTwitchStreamAccessToken* token);
GtTwitchStreamAccessToken* gt_twitch_stream_access_token(GtTwitch* self, const gchar* channel, GError** error);
void                       gt_twitch_stream_access_token_async(GtTwitch* self, const gchar* channel, GCancellable* cancel, GAsyncReadyCallback cb, gpointer udata);
GtTwitchStreamData*        gt_twitch_stream_list_filter_quality(GList* list, GtTwitchStreamQuality qual);
GList*                     gt_twitch_all_streams(GtTwitch* self, const gchar* channel, GError** error);
void                       gt_twitch_all_streams_async(GtTwitch* self, const gchar* channel, GCancellable* cancel, GAsyncReadyCallback cb, gpointer udata);
GList*                     gt_twitch_all_streams_finish(GtTwitch* self, GAsyncResult* result, GError** error);
GList*                     gt_twitch_top_channels(GtTwitch* self, gint n, gint offset, gchar* game, GError** error);
void                       gt_twitch_top_channels_async(GtTwitch* self, gint n, gint offset, gchar* game, GCancellable* cancel, GAsyncReadyCallback cb, gpointer udata);
GList*                     gt_twitch_top_games(GtTwitch* self, gint n, gint offset, GError** error);
void                       gt_twitch_top_games_async(GtTwitch* self, gint n, gint offset, GCancellable* cancel, GAsyncReadyCallback cb, gpointer udata);
GList*                     gt_twitch_top_games_finish(GtTwitch* self, GAsyncResult* result, GError** error);
GList*                     gt_twitch_search_channels(GtTwitch* self, const gchar* query, gint n, gint offset, GError** error);
void                       gt_twitch_search_channels_async(GtTwitch* self, const gchar* query, gint n, gint offset, GCancellable* cancel, GAsyncReadyCallback cb, gpointer udata);
GList*                     gt_twitch_search_channels_finish(GtTwitch* self, GAsyncResult* result, GError** error);
GList*                     gt_twitch_search_games(GtTwitch* self, const gchar* query, gint n, gint offset, GError** error);
void                       gt_twitch_search_games_async(GtTwitch* self, const gchar* query, gint n, gint offset, GCancellable* cancel, GAsyncReadyCallback cb, gpointer udata);
GList*                     gt_twitch_search_games_finish(GtTwitch* self, GAsyncResult* result, GError** error);
void                       gt_twitch_stream_data_free(GtTwitchStreamData* data);
void                       gt_twitch_stream_data_list_free(GList* list);
GtChannelRawData*          gt_twitch_channel_raw_data(GtTwitch* self, const gchar* name);
GtChannelRawData*          gt_twitch_channel_with_stream_raw_data(GtTwitch* self, const gchar* name);
void                       gt_twitch_channel_raw_data_async(GtTwitch* self, const gchar* name, GCancellable* cancel, GAsyncReadyCallback cb, gpointer udata);
void                       gt_twitch_channel_raw_data_free(GtChannelRawData* data);
GtGameRawData*             gt_twitch_game_raw_data(GtTwitch* self, const gchar* name);
void                       gt_twitch_game_raw_data_free(GtGameRawData* data);
GdkPixbuf*                 gt_twitch_download_picture(GtTwitch* self, const gchar* url, gint64 timestamp);
void                       gt_twitch_download_picture_async(GtTwitch* self, const gchar* url, gint64 timestamp, GCancellable* cancel, GAsyncReadyCallback cb, gpointer udata);
GdkPixbuf*                 gt_twitch_download_emote(GtTwitch* self, gint id);
GList*                     gt_twitch_channel_info(GtTwitch* self, const gchar* chan);
void                       gt_twitch_channel_info_panel_free(GtTwitchChannelInfoPanel* panel);
void                       gt_twitch_channel_info_async(GtTwitch* self, const gchar* chan, GCancellable* cancel, GAsyncReadyCallback cb, gpointer udata);
GList*                     gt_twitch_chat_servers(GtTwitch* self, const gchar* chan);
GList*                     gt_twitch_follows(GtTwitch* self, const gchar* user_name, gint limit, gint offset);
void                       gt_twitch_follows_async(GtTwitch* self, const gchar* user_name, gint limit, gint offset, GCancellable* cancel, GAsyncReadyCallback cb, gpointer udata);
GList*                     gt_twitch_follows_all(GtTwitch* self, const gchar* user_name, GError** error);
void                       gt_twitch_follows_all_async(GtTwitch* self, const gchar* user_name, GCancellable* cancel, GAsyncReadyCallback cb, gpointer udata);
GList*                     gt_twitch_follows_all_finish(GtTwitch* self, GAsyncResult* result, GError** error);
void                       gt_twitch_follow_channel(GtTwitch* self, const gchar* chan_name, GError** error);
void                       gt_twitch_follow_channel_async(GtTwitch* self, const gchar* chan_name, GAsyncReadyCallback cb, gpointer udata);
void                       gt_twitch_follow_channel_finish(GtTwitch* self, GAsyncResult* result, GError** error);
void                       gt_twitch_unfollow_channel(GtTwitch* self, const gchar* chan_name, GError** error);
void                       gt_twitch_unfollow_channel_async(GtTwitch* self, const gchar* chan_name, GAsyncReadyCallback cb, gpointer udata);
void                       gt_twitch_unfollow_channel_finish(GtTwitch* self, GAsyncResult* result, GError** error);
GList*                     gt_twitch_emoticons(GtTwitch* self, const gchar* emotesets, GError** error);
void                       gt_twitch_emoticons_async(GtTwitch* self, const char* emotesets, GAsyncReadyCallback cb, GCancellable* cancel, gpointer udata);
void                       gt_twitch_oauth_info_free(GtTwitchOAuthInfo* info);
GtTwitchOAuthInfo*         gt_twitch_oauth_info(GtTwitch* self, GError** error);
void                       gt_twitch_oauth_info_async(GtTwitch* self, GAsyncReadyCallback cb, GCancellable* cancel, gpointer udata);
GtTwitchOAuthInfo*         gt_twitch_oauth_info_finish(GtTwitch* self, GAsyncResult* result, GError** error);
GtChatBadge*               gt_twitch_fetch_chat_badge(GtTwitch* self, gint64 chan_id, const gchar* badge_name, const gchar* version, GError** err);
void                       gt_twitch_fetch_chat_badge_async(GtTwitch* self, gint64 chan_id, const gchar* badge_name, const gchar* version, GCancellable* cancel, GAsyncReadyCallback cb, gpointer udata);
GtChatBadge*               gt_twitch_fetch_chat_badge_finish(GtTwitch* self, GAsyncResult* result, GError** err);
void                       gt_twitch_load_chat_badge_sets_for_channel(GtTwitch* self, gint64 chan_id, GError** err);
void                       gt_chat_badge_free(GtChatBadge* badge);
void                       gt_chat_badge_list_free(GList* list);
GtChatEmote*               gt_chat_emote_new();
void                       gt_chat_emote_free(GtChatEmote* emote);
void                       gt_chat_emote_list_free(GList* list);

G_END_DECLS

#endif
