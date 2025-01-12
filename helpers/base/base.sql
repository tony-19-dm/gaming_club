SELECT name FROM sqlite_master WHERE type='table' AND name='bookings';

INSERT INTO bookings (name, date, start_time, end_time, devices) 
VALUES ('John Doe', '2024-12-10', '10:00', '12:00', '4, 2');
