create table book
(
    id              integer primary key autoincrement,
    title           text not null,
    author          text not null,
    published_year  integer,
    genre           text,
    isbn            text unique
);
