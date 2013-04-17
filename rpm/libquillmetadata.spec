# 
# Do NOT Edit the Auto-generated Part!
# Generated by: spectacle version 0.25
# 

Name:       libquillmetadata

# >> macros
# << macros

Summary:    Qt based library for still image metadata manipulation
Version:    1.111111.0
Release:    0
Group:      System/Libraries
License:    LGPLv2
URL:        https://github.com/nemomobile/quillmetadata
Source0:    meego-image-editor-quillmetadata-%{version}.tar.gz
Source100:  libquillmetadata.yaml
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  pkgconfig(QtCore)
BuildRequires:  pkgconfig(QtGui)
BuildRequires:  pkgconfig(libexif)
BuildRequires:  pkgconfig(exempi-2.0)
BuildRequires:  fdupes
BuildRequires:  libjpeg-devel
BuildRequires:  fdupes

%description
A Qt based library which can access and edit Exif, XMP and IPTC
metadata for still images (currently only JPEG format), offering
transparent reconciliation between different metadata representations.


%package tests
Summary:    Qt based library for still image metadata manipulation - unit tests
Group:      System/Libraries
Requires:   %{name} = %{version}-%{release}
Requires:   testrunner-lite

%description tests
A Qt based library which can access and edit Exif, XMP and IPTC
metadata for still images (currently only JPEG format), offering
transparent reconciliation between different metadata representations.

This package includes the unit tests.


%package devel
Summary:    Qt based library for still image metadata manipulation - development headers
Group:      System/Libraries
Requires:   %{name} = %{version}-%{release}

%description devel
A Qt based library which can access and edit Exif, XMP and IPTC
metadata for still images (currently only JPEG format), offering
transparent reconciliation between different metadata representations.

This package includes the development headers.



%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
qmake
# << build pre


make %{?jobs:-j%jobs}

# >> build post
# << build post

%install
rm -rf %{buildroot}
# >> install pre
# << install pre
%make_install

# >> install post
# Remove duplicate pkgconfig file
rm %{buildroot}/%{_libdir}/quillmetadata.pc
# << install post

%fdupes  %{buildroot}/%{_libdir}/

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
# >> files
%{_libdir}/libquillmetadata*.so.*
# << files

%files tests
%defattr(-,root,root,-)
# >> files tests
%{_libdir}/libquillmetadata-tests/*
%{_datadir}/libquillmetadata-tests/*
# << files tests

%files devel
%defattr(-,root,root,-)
# >> files devel
%{_libdir}/pkgconfig/quillmetadata.pc
%{_includedir}/qt4/quillmetadata/*
%{_libdir}/libquillmetadata.so
%{_datadir}/qt4/mkspecs/features/quillmetadata.prf
# << files devel