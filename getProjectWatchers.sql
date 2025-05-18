SELECT
    u.first_name,
    u.last_name
FROM
    projects p
JOIN departments d ON
    p.department_id = d.id
JOIN users u ON
    u.department_id = d.id
WHERE
    p.name = ?

