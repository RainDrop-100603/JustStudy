from django.urls import path
from django.conf.urls import url
from .views import CalendarView, index

app_name = "calendars"

urlpatterns = [
    url(r"^index/$", index, name="index"),
    url(r"^calendar/$", CalendarView.as_view(), name="calendar"),  # here
]
