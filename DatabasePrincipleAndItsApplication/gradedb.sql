create database gradedb;

create table STUDENT(
	SID serial not null primary key,
	SName varchar(16) not null,
	Age int not null Check(Age > 0),
	Sex varchar(8) not null check(Sex in ('Female', 'Male'))
);

create table COURSE(
	CID serial not null primary key,
	CName varchar(16) not null,
	Teacher varchar(16) not null
);

create table GRADE(
	SID int not null,
	CID int not null,
	Score int not null check(Score > 0),
	Note varchar(100),
	constraint GRADE_PK primary key (SID, CID)
);
