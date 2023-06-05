-- User schema
CREATE TABLE IF NOT EXISTS user (
    id          INTEGER PRIMARY KEY,
    username    TEXT    UNIQUE NOT NULL,
    email       TEXT    UNIQUE NOT NULL,
    password    TEXT    NOT NULL,
    access      INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS config (
    user_id INTEGER UNIQUE NOT NULL,
    theme   INT     DEFAULT 0,
    menu    INT     DEFAULT 1,
    top     INT     DEFAULT 0,
    bottom  INT     DEFAULT 2,
    landing INT     DEFAULT 3,
    FOREIGN KEY(user_id) REFERENCES user(id)
);

CREATE TABLE IF NOT EXISTS guardian (
    child_id    INTEGER NOT NULL,
    guardian_id INTEGER NOT NULL,
    FOREIGN KEY(child_id) REFERENCES user(id),
    FOREIGN KEY(guardian_id) REFERENCES user(id),
    UNIQUE(child_id, guardian_id)
);

-- Profile schema
CREATE TABLE IF NOT EXISTS profile (
    user_id         INTEGER     UNIQUE NOT NULL,
    avatar_id       INTEGER     NOT NULL,
    display_name    TEXT        NOT NULL,
    bio             TEXT        NOT NULL,
    fish_day        TEXT        NOT NULL,
    theme           INTEGER     NOT NULL,
    FOREIGN KEY(user_id) REFERENCES user(id),
    FOREIGN KEY(avatar_id) REFERENCES avatar(id)
);

CREATE TABLE IF NOT EXISTS pal (
    user_id     INTEGER     NOT NULL,
    id          INTEGER     PRIMARY KEY,
    avatar_id   INTEGER     NOT NULL,
    name        TEXT        NOT NULL,
    species     TEXT        NOT NULL,
    birthday    TEXT        NOT NULL,
    bio         TEXT        NOT NULL,
    FOREIGN KEY(user_id) REFERENCES user(id),
    FOREIGN KEY(avatar_id) REFERENCES avatar(id)
);

CREATE TABLE IF NOT EXISTS avatar (
    id      INT PRIMARY KEY,
    content BLOB NOT NULL
);

CREATE TABLE IF NOT EXISTS link (
    user_id INTEGER NOT NULL,
    label TEXT NOT NULL,
    link TEXT NOT NULL,
    FOREIGN KEY(user_id) REFERENCES user(id),
    UNIQUE(user_id, label, link)
);

CREATE TABLE IF NOT EXISTS reef (
    from_user_id    INTEGER NOT NULL,
    to_user_id      INTEGER NOT NULL,
    FOREIGN KEY(from_user_id) REFERENCES user(id),
    FOREIGN KEY(to_user_id) REFERENCES user(id),
    UNIQUE(from_user_id, to_user_id)
);

CREATE TABLE IF NOT EXISTS shoal_membership (
    member_id   INT     NOT NULL,
    shoal_tag   TEXT    NOT NULL,
    FOREIGN KEY (member_id) REFERENCES user(id),
    FOREIGN KEY (shoal_tag) REFERENCES shoal(tag),
    UNIQUE(member_id, shoal_tag)
);

-- Content schema
CREATE TABLE IF NOT EXISTS post (
    id          INTEGER PRIMARY KEY,
    creator_id  INTEGER NOT NULL,
    shoal_tag   TEXT NOT NULL,
    message     TEXT NOT NULL,
    post_date   TEXT NOT NULL,
    image_id    INTEGER,
    trade_id    INTEGER,
    survey_id   INTEGER,
    event_id    INTEGER,
    FOREIGN KEY(creator_id) REFERENCES user(id),
    FOREIGN KEY(shoal_tag) REFERENCES shoal(tag),
    FOREIGN KEY(image_id) REFERENCES image(id),
    FOREIGN KEY(trade_id) REFERENCES trade(id),
    FOREIGN KEY(survey_id) REFERENCES survey(id),
    FOREIGN KEY(event_id) REFERENCES event(id)
);

CREATE TABLE IF NOT EXISTS shoal (
    tag         TEXT    PRIMARY KEY,
    theme       INT     NOT NULL,
    description TEXT    NOT NULL,
    creator_id  INTEGER NOT NULL,
    FOREIGN KEY(creator_id) REFERENCES user(id)
);

CREATE TABLE IF NOT EXISTS image (
    id      INTEGER PRIMARY KEY,
    content BLOB NOT NULL
);

CREATE TABLE IF NOT EXISTS trade (
    id              INTEGER PRIMARY KEY,
    pal_offer_id    INTEGER NOT NULL,
    offer_alt       TEXT NOT NULL,
    pal_seek_id     INTEGER NOT NULL,
    seek_alt        TEXT NOT NULL,
    FOREIGN KEY(pal_offer_id) REFERENCES pal(id),
    FOREIGN KEY(pal_seek_id) REFERENCES pal(id)
);

CREATE TABLE IF NOT EXISTS survey (
    id          INTEGER PRIMARY KEY,
    opt1msg     TEXT    NOT NULL,
    opt2msg     TEXT    NOT NULL,
    opt3msg     TEXT    NOT NULL,
    opt4msg     TEXT    NOT NULL,
    opt1votes   INTEGER NOT NULL,
    opt2votes   INTEGER NOT NULL,
    opt3votes   INTEGER NOT NULL,
    opt4votes   INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS event (
    id          INTEGER PRIMARY KEY,
    title       TEXT NOT NULL,
    start       TEXT NOT NULL,
    end         TEXT NOT NULL,
    link_label  TEXT NOT NULL,
    link        TEXT NOT NULL
);

--Chat schema
CREATE TABLE IF NOT EXISTS chat (
    id      INTEGER PRIMARY KEY,
    title   TEXT    NOT NULL,
    theme   INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS chat_membership (
    chat_id     INTEGER NOT NULL,
    member_id   INTEGER NOT NULL,
    unread      INTEGER NOT NULL DEFAULT 1,
    FOREIGN KEY(chat_id) REFERENCES chat(id),
    FOREIGN KEY(member_id) REFERENCES user(id),
    UNIQUE (chat_id, member_id)
);

CREATE TABLE IF NOT EXISTS message (
    id          INTEGER PRIMARY KEY,
    author_id   INTEGER NOT NULL,
    chat_id     INTEGER NOT NULL,
    message     TEXT    NOT NULL,
    send_date   TEXT    NOT NULL,
    FOREIGN KEY(author_id) REFERENCES user(id),
    FOREIGN KEY(chat_id) REFERENCES chat(id)
);

--Monitor schema
CREATE TABLE IF NOT EXISTS post_report (
    post_id     INTEGER NOT NULL,
    reporter_id INTEGER NOT NULL,
    FOREIGN KEY(post_id) REFERENCES post(id),
    FOREIGN KEY(reporter_id) REFERENCES user(id),
    UNIQUE(post_id, reporter_id)
);

CREATE TABLE IF NOT EXISTS profile_report (
    reported_user_id    INTEGER NOT NULL,
    reporter_id         INTEGER NOT NULL,
    FOREIGN KEY(reported_user_id) REFERENCES user(id),
    FOREIGN KEY(reporter_id) REFERENCES user(id),
    UNIQUE(reported_user_id, reporter_id)
);

CREATE TABLE IF NOT EXISTS message_report (
    message_id  INTEGER NOT NULL,
    reporter_id INTEGER NOT NULL,
    FOREIGN KEY(message_id) REFERENCES message(id),
    FOREIGN KEY(reporter_id) REFERENCES user(id),
    UNIQUE(message_id, reporter_id)
);

.separator ","
.mode csv
.import "./user.csv"        user
.import "./config.csv"      config
.import "./guardian.csv"    guardian

.separator "|"
.import "./profile.csv" profile
.import "./pal.csv"     pal
.import "./message.csv" message
.import "./shoal.csv"   shoal
.import "./post.csv"    post

.separator ","
.import "./link.csv"                link
.import "./reef.csv"                reef
.import "./shoal_membership.csv"    shoal_membership

.import "./event.csv"   event
.import "./trade.csv"   trade
.import "./survey.csv"  survey

.import "./chat.csv"            chat
.import "./chat_membership.csv" chat_membership

.import "./profile_report.csv"  profile_report
.import "./post_report.csv"     post_report
.import "./message_report.csv"  message_report