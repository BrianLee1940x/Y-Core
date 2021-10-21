CREATE TABLE IF NOT EXISTS `player_stats`
(
    `p_id` bigint(20) UNSIGNED NOT NULL,
    `developer` tinyint(1) NOT NULL DEFAULT 0,
    `gender` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
    `race` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
    `money` bigint(20) NOT NULL DEFAULT 0,
    `xp` int(11) UNSIGNED NOT NULL DEFAULT 0,
    `skin` smallint(4) NOT NULL DEFAULT 0,
    `spawnType` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
    `lastPosX` float NOT NULL DEFAULT 0.0,
    `lastPosY` float NOT NULL DEFAULT 0.0,
    `lastPosZ` float NOT NULL DEFAULT 0.0,
    `lastAng` float NOT NULL DEFAULT 0.0,
    `lastWorld` int(11) NOT NULL DEFAULT 0,
    `lastInt` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
    PRIMARY KEY
        (p_id),
    FOREIGN KEY
        (p_id)
    REFERENCES
        accounts(u_id)
    ON DELETE
        CASCADE
    ON UPDATE
        NO ACTION
);