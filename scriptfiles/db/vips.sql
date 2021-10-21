CREATE TABLE IF NOT EXISTS vips (
    p_id bigint(20) UNSIGNED AUTO_INCREMENT,
    vip_level TINYINT(2) NOT NULL DEFAULT 0,
    vip_expire_date datetime NULL,
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