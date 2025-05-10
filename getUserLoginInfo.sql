SELECT
    id,
    first_name,
    ROLE
FROM
    ticket_system.users
WHERE
    email = :email
    AND password = :password
