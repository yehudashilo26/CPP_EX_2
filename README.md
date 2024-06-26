<div directon="rtl" style="text-align: right">

# מטלה 2 - גרפים והעמסת אופרטורים

#### במטלה זו נממש העמסת אופרטורים עבור מחלקת הגרף שכתבנו במטלה 1.

## ההעמסה תתבצע עבור האופרטורים הבאים:

### אופרטורי השוואה:

1. `שווה - ==` משווה בין שני גרפים ובודק אם הם שווים.
2. `שונה - !=` משווה בין שני גרפים ובודק אם הם שונים.
3. `קטן מ - <` משווה בין שני גרפים ובודק אם הראשון קטן מהשני.
4. `גדול מ - >` משווה בין שני גרפים ובודק אם הראשון גדול מהשני.
5. `קטן או שווה - <=` משווה בין שני גרפים ובודק אם הראשון קטן או שווה לשני.
6. `גדול או שווה - >=` משווה בין שני גרפים ובודק אם הראשון גדול או שווה לשני.

### אופרטורים בינאריים:

1. `חיבור - +` מחבר בין שני גרפים ומחזיר גרף חדש שהוא תוצאת החיבור.
2. `חיסור - - ` מחסר בין שני גרפים ומחזיר גרף חדש שהוא תוצאת החיסור.
3. `כפל - *` מכפיל בין שני גרפים או גרף וסקלר ומחזיר גרף חדש שהוא תוצאת הכפל.
4. `הוספה - +=` מוסיף את הגרף השני לגרף הראשון.
5. `החסרה - -=` מחסיר את הגרף השני מהגרף הראשון.
6. `הכפלה - *=` מכפיל את הגרף הראשון בגרף השני או בסקלר.

### אופרטורים אונריים:

1. `הפיכת הסימן - -`
2. `השארת הסימן - +`

### אופרטורי קידום והפחתה:

1. `קידום Postfix - ++(int)`
2. `הפחתה Postfix - --(int)`
3. `קידום Prefix - ++`
4. `הפחתה Prefix - --`

### אופרטורי פלט:

1. `>>` - העברה של ייצוג הגרף לפלט , משמש גם להדפסת הגרף למסך.

---

##מימוש ההעמסה:

במחלקה גרף דרסנו את האופרטורים הנ"ל ומימשנו אותם בהתאם לפעולה של כל אופרטור.

במימוש אופרטורי ההשוואה השתמשנו בחוקים לוגיים על מנת לחסוך בכמות הקוד הנדרש למימוש האופרטורים.

מימשנו את אופרטור גדול מ- על פי הקריטריונים הבאים:

1. הגרף הראשון גדול מהגרף השני אם הגרף השני מוכל ממש בגרף הראשון.
2. הגרף הראשון גדול מהגרף השני אם מספר הקשתות בגרף הראשון גדול ממספר הקשתות בגרף השני.
3. הגרף הראשון גדול מהגרף השני אם מספר הקודקודים בגרף הראשון גדול ממספר הקודקודים בגרף השני.

לאחר מכן השתמשנו בחוקים הלוגיים הבאים על מנת לממש את שאר אופרטורי ההשוואה:

<div style="text-align:left">

```cpp
bool Graph::operator<(const Graph &other) const {
    return other > *this;
}

bool Graph::operator>=(const Graph &other) const {
return !(*this < other) || (*this == other);
} // אם הגרף הראשון קטן מהשני אז הוא לא גדול או שווה לשני או.

bool Graph::operator<=(const Graph &other) const {
return other >= \*this ;
} // אם הגרף השני גדול-שווה לראשון אז הראשון קטן או שווה לשני.

bool Graph::operator==(const Graph &other) const {
return (*this > other) && (other > *this);
} // אם הגרף הראשון גדול מהשני והשני גדול מהראשון אז הם שווים , מוכלים אחד בשני.

bool Graph::operator!=(const Graph &other) const {
return !(\*this == other);
} // אם הגרף הראשון שונה מהשני אז הם לא שווים.

```

</div>

### מימוש אופרטורים בינאריים:

חיבור + :
האופרטור מחבר את המטריצות של שני הגרפים ומחזיר גרף חדש עם מטריצה מחוברת. אם הגרפים לא באותו גודל, תיזרק חריגה.

חיסור - :
האופרטור מחסר את המטריצות של שני הגרפים ומחזיר גרף חדש עם מטריצה מחוסרת. אם הגרפים לא באותו גודל, תיזרק חריגה.

כפל \* :
האופרטור מבצע כפל מטריצות של שני הגרפים ומחזיר גרף חדש עם מטריצה מכופלת. כמו כן, אפשר לכפול גרף בסקלר. אם הגרפים לא באותו גודל, תיזרק חריגה.

הוספה += :
האופרטור מוסיף את המטריצה של הגרף השני למטריצה של הגרף הראשון.

החסרה -= :
האופרטור מחסר את המטריצה של הגרף השני מהמטריצה של הגרף הראשון.

הכפלה \*= :
האופרטור מכפיל את המטריצה של הגרף הראשון במטריצה של הגרף השני או בסקלר.

### מימוש אופרטורים אונריים:

הפיכת הסימן - :
האופרטור מחזיר גרף חדש עם כל הערכים במטריצה עם סימן הפוך.

השארת הסימן + :
האופרטור מחזיר את הגרף כפי שהוא.

### מימוש אופרטורי קידום והפחתה:

קידום Postfix ++(int) :
האופרטור מעלה את כל הערכים במטריצה ב-1 ומחזיר את הגרף לפני הקידום.

הפחתה Postfix --(int) :
האופרטור מוריד את כל הערכים במטריצה ב-1 ומחזיר את הגרף לפני ההפחתה.

קידום Prefix ++ :
האופרטור מעלה את כל הערכים במטריצה ב-1 ומחזיר את הגרף אחרי הקידום.

הפחתה Prefix -- :
האופרטור מוריד את כל הערכים במטריצה ב-1 ומחזיר את הגרף אחרי ההפחתה.

### מימוש אופרטור פלט:

<< :
האופרטור מעביר את ייצוג הגרף לפלט ומאפשר הדפסה נוחה של הגרף למסך או לכל ostream אחר.

</div>
