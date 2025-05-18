SELECT
	t.title,
	t.description,
	p.name AS project,
	tr.name AS tracker,
	s.name AS status,
	pr.name AS priority,
	u1.full_name AS assignee,
	u2.full_name AS watcher,
	t.attachment,
	t.created_at
FROM
	tickets t
JOIN projects p ON
	t.project_id = p.id
JOIN trackers tr ON
	t.tracker_id = tr.id
JOIN statuses s ON
	t.status_id = s.id
JOIN priorities pr ON
	t.priority_id = pr.id
JOIN users u1 ON
	t.assignee_id = u1.id
JOIN users u2 ON
	t.watcher_id = u2.id
WHERE
	t.id = :ticketId
