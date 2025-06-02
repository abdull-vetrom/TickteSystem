SELECT
    t.id,
    t.title,
    tr.name AS tracker
FROM
    tickets t
JOIN trackers tr ON
    t.tracker_id = tr.id
WHERE
    t.assignee_id = :userId
ORDER BY
    t.id DESC;
