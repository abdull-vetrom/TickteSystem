SELECT
	first_name,
	last_name,
	email,
	ROLE,
	department
FROM
	users
WHERE
	id = :id
