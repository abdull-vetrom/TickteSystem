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
    :first,
    :last,
    :middle,
    :email,
    :password,
    :role,
    :dept,
    :full
)
