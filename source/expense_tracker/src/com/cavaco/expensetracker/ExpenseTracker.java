

package com.cavaco.expensetracker;

import android.net.Uri;
import android.provider.BaseColumns;

/**
 * Provides access to a database of expenses. Each expense has a type, an amount,
 * a date, a currency, and a note.
 */


public final class ExpenseTracker {
    public static final String AUTHORITY = "com.google.provider.ExpenseTracker";
	
    // This class cannot be instantiated
	private ExpenseTracker() {
	}
   
	/**
	 * Expenses table Contract
	 */
	public static final class Expenses implements BaseColumns {
		
        // This class cannot be instantiated
		private Expenses() {}
		
		public static final String TABLE_NAME = "expenses";
		
        /*
         * URI definitions
         */

        /**
         * The scheme part for this provider's URI
         */
        private static final String SCHEME = "content://";

        /**
         * Path parts for the URIs
         */

        /**
         * Path part for the Notes URI
         */
        private static final String PATH_EXPENSES = "/expenses";

        /**
         * Path part for the Note ID URI
         */
        private static final String PATH_EXPENSE_ID = "/expenses/";

        /**
         * 0-relative position of an expense ID segment in the path part of a expense ID URI
         */
        public static final int EXPENSE_ID_PATH_POSITION = 1;

        /**
         * Path part for the Live Folder URI
         */
        private static final String PATH_LIVE_FOLDER = "/live_folders/expenses";

        /**
         * The content:// style URL for this table
         */
        public static final Uri CONTENT_URI =  Uri.parse(SCHEME + AUTHORITY + PATH_EXPENSES);

        /**
         * The content URI base for a single note. Callers must
         * append a numeric note id to this Uri to retrieve a note
         */
        public static final Uri CONTENT_ID_URI_BASE
            = Uri.parse(SCHEME + AUTHORITY + PATH_EXPENSE_ID);

        /**
         * The content URI match pattern for a single note, specified by its ID. Use this to match
         * incoming URIs or to construct an Intent.
         */
        public static final Uri CONTENT_ID_URI_PATTERN
            = Uri.parse(SCHEME + AUTHORITY + PATH_EXPENSE_ID + "/#");

        /**
         * The content Uri pattern for a notes listing for live folders
         */
        public static final Uri LIVE_FOLDER_URI
            = Uri.parse(SCHEME + AUTHORITY + PATH_LIVE_FOLDER);

        /*
         * MIME type definitions
         */

        /**
         * The MIME type of {@link #CONTENT_URI} providing a directory of notes.
         */
        public static final String CONTENT_TYPE = "vnd.android.cursor.dir/vnd.google.expense";

        /**
         * The MIME type of a {@link #CONTENT_URI} sub-directory of a single
         * note.
         */
        public static final String CONTENT_ITEM_TYPE = "vnd.android.cursor.item/vnd.google.expense";

        /**
         * The default sort order for this table
         */
        public static final String DEFAULT_SORT_ORDER = "modified DESC";

        /*
         * Column definitions
         */

        /**
         * Column name for the date
         * <P>Type: INTEGER (long from System.curentTimeMillis())</P>
         */
        public static final String COLUMN_NAME_DATE = "date";

        /**
         * Column name for the type of the expense
         * <P>Type: TEXT</P>
         */
        public static final String COLUMN_NAME_TYPE = "type";

        /**
         * Column name of the amount
         * <P>Type: FLOAT</P>
         */
        public static final String COLUMN_NAME_AMOUNT = "amount";

        /**
         * Column name for the note
         * <P>Type: TEXT</P>
         */
        public static final String COLUMN_NAME_NOTE = "note";

        /**
         * Column name for the creation currency
         * <P>Type: TEXT</P>
         */
        public static final String COLUMN_NAME_CURRENCY = "currency";
	}

	public static final class Types implements BaseColumns {
		private Types() {}
		
		public static final String TABLE_NAME = "types";
		
        /*
         * URI definitions
         */

        /**
         * The scheme part for this provider's URI
         */
        private static final String SCHEME = "content://";

        /**
         * Path parts for the URIs
         */

        /**
         * Path part for the Notes URI
         */
        private static final String PATH_TYPES = "/types";

        /**
         * Path part for the Note ID URI
         */
        private static final String PATH_TYPE_ID = "/types/";

        /**
         * 0-relative position of an expense ID segment in the path part of a expense ID URI
         */
        public static final int EXPENSE_ID_PATH_POSITION = 1;

        /**
         * Path part for the Live Folder URI
         */
        private static final String PATH_LIVE_FOLDER = "/live_folders/types";

        /**
         * The content:// style URL for this table
         */
        public static final Uri CONTENT_URI =  Uri.parse(SCHEME + AUTHORITY + PATH_TYPES);

        /**
         * The content URI base for a single note. Callers must
         * append a numeric note id to this Uri to retrieve a note
         */
        public static final Uri CONTENT_ID_URI_BASE
            = Uri.parse(SCHEME + AUTHORITY + PATH_TYPE_ID);

        /**
         * The content URI match pattern for a single note, specified by its ID. Use this to match
         * incoming URIs or to construct an Intent.
         */
        public static final Uri CONTENT_ID_URI_PATTERN
            = Uri.parse(SCHEME + AUTHORITY + PATH_TYPE_ID + "/#");

        /**
         * The content Uri pattern for a notes listing for live folders
         */
        public static final Uri LIVE_FOLDER_URI
            = Uri.parse(SCHEME + AUTHORITY + PATH_LIVE_FOLDER);

        /*
         * MIME type definitions
         */

        /**
         * The MIME type of {@link #CONTENT_URI} providing a directory of notes.
         */
        public static final String CONTENT_TYPE = "vnd.android.cursor.dir/vnd.google.type";

        /**
         * The MIME type of a {@link #CONTENT_URI} sub-directory of a single
         * note.
         */
        public static final String CONTENT_ITEM_TYPE = "vnd.android.cursor.item/vnd.google.type";

        /**
         * The default sort order for this table
         */
        public static final String DEFAULT_SORT_ORDER = "modified DESC";

        /*
         * Column definitions
         */

        /**
         * Column name for the type
         * <P>Type: TEXT</P>
         */
        public static final String COLUMN_NAME_NAME = "name";

        /**
         * Column name for the type
         * <P>Type: TEXT</P>
         */
        public static final String COLUMN_NAME_TYPE = "type";
	}
}