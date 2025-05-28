INSERT INTO users (
	first_name,
	last_name,
	middle_name,
	email,
	password,
	ROLE,
	department_id,
	full_name
)
VALUES (
	:FIRST,
	:LAST,
	:middle,
	:email,
	:password,
	:ROLE,
	:dept,
	:FULL
)
