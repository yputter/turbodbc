PostgreSQL
==========

`PostgreSQL <https://www.postgresql.org>`_ is part of turbodbc's
integration databases. That means that each commit in turbodbc's repository
is automatically tested against PostgreSQL to ensure compatibility.
Here are the recommended settings for connecting to a PostgreSQL database via ODBC
using the turbodbc module for Python.

.. note::
    PostgreSQL's free ODBC driver is not optimized for performance. Hence, there
    is not too much turbodbc can do to improve speed. You will achieve much better
    performance with `psycopg2 <https://github.com/psycopg/psycopg2>`_ or
    `asyncpg <https://github.com/MagicStack/asyncpg>`_.


Recommended odbcinst.ini (Linux)
--------------------------------

.. code-block:: ini

    [PostgreSQL Driver]
    Driver      = /usr/lib/x86_64-linux-gnu/odbc/psqlodbcw.so
    Threading   = 2

*   ``Threading = 2`` is a safe choice to avoid potential thread issues with the driver,
    but you can also attempt using the driver without this option.


Recommended odbcinst.ini (OSX)
------------------------------

.. code-block:: ini

    [PostgreSQL Driver]
    Driver      = /usr/local/lib/psqlodbcw.so
    Threading   = 2

*   ``Threading = 2`` is a safe choice to avoid potential thread issues with the driver,
    but you can also attempt using the driver without this option.


Recommended data source configuration
-------------------------------------

.. code-block:: ini

    [PostgreSQL]
    Driver               = PostgreSQL Driver
    Database             = <database name>
    Servername           = <host>
    UserName             = <user>
    Password             = <password>
    Port                 = <port, default is 5432>
    Protocol             = 7.4
    UseDeclareFetch      = 1
    Fetch                = 10000
    UseServerSidePrepare = 1
    BoolsAsChar          = 0
    ConnSettings         = set time zone 'UTC';

*   ``Protocol = 7.4`` indicates version 3 of the PostgreSQL protocol is to be
    used, which is the latest one.
*   ``UseDeclareFetch = 1`` means that the driver will only cache a few lines of
    the result set instead of the entire result set (which may easily eat up all
    available memory). The downside is that PostgreSQL will always cache exactly
    ``Fetch`` lines, no matter what the ODBC application (including turbodbc)
    actually requires.
*   ``Fetch = 10000`` tells the PostgreSQL ODBC driver to fetch results from the
    database exactly in batches of 10,000 rows (no matter what turbodbc or any
    other ODBC application declares as the batch size). Using a high value may
    improve performance, but increases memory consumption in particular for
    tables with many columns. Low values reduces the memory footprint, but
    increases the number of database roundtrips, which may dominate performance
    for large result sets. The default value is 100.
*   ``UseServerSidePrepare = 1`` means the server will prepare queries rather
    than the ODBC driver. This yields the most accurate results concerning
    result sets.
*   ``BoolsAsChar = 0`` tells the driver to return boolean fields as booleans
    (``SQL_BIT`` in ODBC-speak) instead of characters. Turbodbc can deal with
    booleans, so make sure to use them.
*   ``ConnSettings = set time zone 'UTC';`` sets the session time zone to
    UTC. This will yield consistent values for fields of types ``WITH TIME ZONE``
    information.

.. note::
    ODBC configuration files generated by the PostgreSQL generation utility
    use the string ``No`` to deactivate options. It is recommended to replace
    all occurrences of ``No`` with ``0``. The reason is that ``Yes`` will not
    work as expected, and also deactivate the option. Use ``1`` instead of ``Yes``
    to get the desired result.



Recommended turbodbc configuration
----------------------------------

The default turbodbc connection options work fine for PostgreSQL. As stated
above, performance is not great due to the ODBC driver.

::

    >>> from turbodbc import connect
    >>> connect(dsn="PostgreSQL")
