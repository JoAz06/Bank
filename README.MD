For the database we require the following:
	- Account table that contains :
		int accountNumber
		double balance
		Person owner
	- Person table that contains :
		int id
		string name
	- Owning table that contains :
		int accountNumber
		int personId

SQL queries :
create table if not exist Account(
	accountNumber int primary key,
	balance double,
	owner int not null,
	foreign key (owner) references Person(id)
);
create table if not exist Person(
	id int primary key,
	name varchar(255) not null
);
create table if not exist Owning(
	owner int not null,
	accountNumber int not null,
	foreighn key (owner) references Person(id),
	foreign key (accountNumber) references Account(accountNumber),
	delete on cascade
);

Select queries :
select from 